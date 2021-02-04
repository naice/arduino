#include <SPI.h>
#include <ESP8266WiFi.h>
#include <XPT2046_Touchscreen.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <ArduinoJson.h>
#include <MiniGrafx.h>
#include <ILI9341_SPI.h>
#include <simpleDSTadjust.h>
#include <JTimeout.h>
#include "arial_rounded.h"
#include "weather_icons.h"
#include "weatherman_logo.h"

/************************* WiFi Access Point *********************************/
#define WLAN_SSID               "Nightlife2.4"
#define WLAN_PASS               "!derm1985"

/************************* MQTT Setup *********************************/

#define AIO_SERVER              "192.168.2.114"
#define AIO_SERVERPORT          1883                   // use 8883 for SSL
#define AIO_USERNAME            "."
#define AIO_KEY                 "."

/************************* TFT Setup *********************************/
 
#define TFT_CS    D2     // TFT CS  pin is connected to NodeMCU pin D2
#define TFT_RST   D3     // TFT RST pin is connected to NodeMCU pin D3
#define TFT_DC    D4     // TFT DC  pin is connected to NodeMCU pin D4
#define TFT_LED   D8

#define TOUCH_CS  D1
#define TOUCH_IRQ D0

#define MINI_BLACK 0
#define MINI_WHITE 1
#define MINI_YELLOW 2
#define MINI_BLUE 3

#define MAX_FORECASTS 12

// change for different NTP (time servers)
#define NTP_SERVERS "0.de.pool.ntp.org", "1.de.pool.ntp.org", "2.de.pool.ntp.org"
// #define NTP_SERVERS "us.pool.ntp.org", "time.nist.gov", "pool.ntp.org"

// August 1st, 2018
#define NTP_MIN_VALID_EPOCH 1533081600

// defines the colors usable in the paletted 16 color frame buffer
uint16_t palette[] = {ILI9341_BLACK, // 0
                      ILI9341_WHITE, // 1
                      ILI9341_YELLOW, // 2
                      0x7E3C
                      }; //3

int SCREEN_WIDTH = 240;
int SCREEN_HEIGHT = 320;
// Limited to 4 colors due to memory constraints
int BITS_PER_PIXEL = 2; // 2^2 =  4 colors

ADC_MODE(ADC_VCC);


ILI9341_SPI tft = ILI9341_SPI(TFT_CS, TFT_DC);
MiniGrafx gfx = MiniGrafx(&tft, BITS_PER_PIXEL, palette);
//XPT2046_Touchscreen ts(TOUCH_CS);
// Wifi
WiFiClient client;
// MQTT
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
// Pubs
Adafruit_MQTT_Publish retentionRequestWeatherCurrent = Adafruit_MQTT_Publish(&mqtt, "retention/request");
// Subs
Adafruit_MQTT_Subscribe retentionWeatherCurrent = Adafruit_MQTT_Subscribe(&mqtt, "retention/weather/current/light");
Adafruit_MQTT_Subscribe weatherCurrent = Adafruit_MQTT_Subscribe(&mqtt, "weather/current/light");

// JSON Weather Data
const size_t capacityWeather = JSON_OBJECT_SIZE(11) + 140;
DynamicJsonDocument docWeather(capacityWeather);

// Time 
#define UTC_OFFSET +1
struct dstRule StartRule = {"CEST", Last, Sun, Mar, 2, 3600}; // Central European Summer Time = UTC/GMT +2 hours
struct dstRule EndRule = {"CET", Last, Sun, Oct, 2, 0};       // Central European Time = UTC/GMT +1 hour
time_t dstOffset = 0;
simpleDSTadjust dstAdjusted(StartRule, EndRule);

// Timeouts
JTimeout timeoutTimeFetched(60000);
JTimeout timeoutRetentionRequest(2000, true);

void setup() {
  Serial.begin(115200);
  pinMode(TFT_LED, OUTPUT);
  digitalWrite(TFT_LED, HIGH);    // HIGH to Turn on;

  gfx.init();
  gfx.fillBuffer(MINI_BLACK);
  gfx.commit();

  drawDialog(String("Connecting WIFI [") + String(WLAN_SSID) + String("]"));
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  char pts[4] = {0};
  int idx = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    memset(&pts, 0, 4);
    memset(&pts, '.', idx++ % 4);
    drawDialog(String("Connecting WIFI [") + String(WLAN_SSID) + String("]\n") + String(pts));
  }
  Serial.println();  

  doSubscription(&weatherCurrent);
  doSubscription(&retentionWeatherCurrent);
  MQTT_connect(true);

  updateNtp(true);

  drawDialog(String("Connected, waiting for data!"));
}

void doSubscription(Adafruit_MQTT_Subscribe *sub) {
  bool isSubsciptionOk;  
  isSubsciptionOk = mqtt.subscribe(sub);
  Serial.print("Subscribed "); Serial.print(sub->topic); Serial.print("... "); Serial.println(isSubsciptionOk ? "OK" : "ERROR");
}
 
bool isWeatherDataPresent = false;

const String WDAY_NAMES[] = {"SON", "MON", "DIE", "MIT", "DON", "FRE", "SAM"};
const String MONTH_NAMES[] = {"JAN", "FEB", "MAR", "APR", "MAI", "JUN", "JUL", "AUG", "SEP", "OKT", "NOV", "DEZ"};
const String HIMMELSRICHTUNGEN[] = {"N", "NNO", "NO", "ONO", "O", "OSO", "SO", "SSO", "S", "SSW", "SW", "WSW", "W", "WNW", "NW", "NNW"};

float temp  = 0;
float feels_like = 0;
const char* city = "";
const char* description = "";
const char* icon = "";
int visibility = 0; // 10000
float windspeed = 0; // 1.5
int winddeg = 0; // 160
int humidity = 0; // 50
int pressure = 0; // 1025
int clouds = 0; // 17
 
void loop(void) {  
  gfx.fillBuffer(MINI_BLACK);
  
  drawWifiQuality();
  MQTT_connect();

  if (!isWeatherDataPresent && timeoutRetentionRequest.CanExecute()) {
    // request retained weather info.
    mqtt.publish("retention/request", "{\"topics\":[\"weather/current/light\"]}");
  }

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(1000))) {
    if (subscription == &retentionWeatherCurrent) {
      Serial.println("weather retention received.");
      updateWeatherData((char*) retentionWeatherCurrent.lastread);
      mqtt.unsubscribe(&retentionWeatherCurrent);
    }
    if (subscription == &weatherCurrent) {
      Serial.println("weather received.");
      updateWeatherData((char*) weatherCurrent.lastread);
      mqtt.unsubscribe(&retentionWeatherCurrent);
    }
  }

  if (timeoutTimeFetched.CanExecute()) {
    updateNtp(false);
  }

  drawTime();
  
  // only draw weather when data present.
  if (isWeatherDataPresent) {
    drawCurrentWeather();
    drawCurrentWeatherDetail();
  }

  gfx.commit();
}

void updateNtp(bool showDialog) {
  time_t now;
  configTime(UTC_OFFSET * 3600, 0, NTP_SERVERS);

  char pts[4] = {0};
  int idx = 0;
  while((now = time(nullptr)) < NTP_MIN_VALID_EPOCH) {
    delay(500);
    
    if (showDialog) {
      memset(&pts, 0, 4);
      memset(&pts, '.', idx++ % 4);
      drawDialog(String("Request Time by NTP\n") + String(pts));
    }
  }
  Serial.println();
  Serial.printf("Current time: %d\n", now);
  // calculate for time calculation how much the dst class adds.
  dstOffset = UTC_OFFSET * 3600 + dstAdjusted.time(nullptr) - now;
  Serial.printf("Time difference for DST: %d\n", dstOffset);
}

void updateWeatherData(char * jsonWeather) {

  if (jsonWeather == NULL) return;

  deserializeJson(docWeather, jsonWeather);

  temp = docWeather["temp"]; // 21.93
  feels_like = docWeather["feels_like"]; // 18.44
  city = docWeather["city"]; // "Dortmund"
  description = docWeather["description"]; // "Bedeckt"
  icon = docWeather["icon"]; // "02n"
  visibility = docWeather["visibility"]; // 10000
  windspeed = docWeather["windspeed"]; // 1.5
  winddeg = docWeather["winddeg"]; // 160
  humidity = docWeather["humidity"]; // 50
  pressure = docWeather["pressure"]; // 1025
  clouds = docWeather["clouds"]; // 17

  isWeatherDataPresent = true;
}


// draws the clock
void drawTime() {
  char time_str[11];
  char *dstAbbrev;
  time_t now = dstAdjusted.time(&dstAbbrev);
  struct tm * timeinfo = localtime (&now);

  gfx.setTextAlignment(TEXT_ALIGN_CENTER);
  gfx.setFont(ArialRoundedMTBold_14);
  gfx.setColor(MINI_WHITE);
  String date = WDAY_NAMES[timeinfo->tm_wday] + " " + MONTH_NAMES[timeinfo->tm_mon] + " " + String(timeinfo->tm_mday) + " " + String(1900 + timeinfo->tm_year);
  gfx.drawString(120, 6, date);

  gfx.setFont(ArialRoundedMTBold_36);
  sprintf(time_str, "%02d:%02d:%02d\n",timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
  gfx.drawString(120, 20, time_str);

  gfx.setTextAlignment(TEXT_ALIGN_LEFT);
  gfx.setFont(ArialMT_Plain_10);
  gfx.setColor(MINI_BLUE);
  
  sprintf(time_str, "%s", dstAbbrev);
  gfx.drawString(195, 27, time_str);  // Known bug: Cuts off 4th character of timezone abbreviation
}

void drawCurrentWeather() {
  gfx.setTransparentColor(MINI_BLACK);
  gfx.drawPalettedBitmapFromPgm(0, 55, getMeteoconIconFromProgmem(icon));
  // Weather Text

  gfx.setFont(ArialRoundedMTBold_14);
  gfx.setColor(MINI_BLUE);
  gfx.setTextAlignment(TEXT_ALIGN_RIGHT);
  gfx.drawString(220, 65, city);

  gfx.setFont(ArialRoundedMTBold_36);
  gfx.setColor(MINI_WHITE);
  gfx.setTextAlignment(TEXT_ALIGN_RIGHT);
    
  gfx.drawString(220, 78, String(temp, 1) + "°C");

  gfx.setFont(ArialRoundedMTBold_14);
  gfx.setColor(MINI_YELLOW);
  gfx.setTextAlignment(TEXT_ALIGN_RIGHT);
  gfx.drawString(220, 118, description);

}

void drawCurrentWeatherDetail() {
  String degreeSign = "°C";
  gfx.setFont(ArialRoundedMTBold_14);
  drawLabelValue(0, "Wind:", String(windspeed, 1) + "m/s");
  drawLabelValue(1, "Richtung:", HIMMELSRICHTUNGEN[windDegTo16(winddeg)]);
  drawLabelValue(2, "Luftfeuchtigkeit:", String(humidity) + "%");
  drawLabelValue(3, "Druck:", String(pressure) + "hPa");
  drawLabelValue(4, "Wolken:", String(clouds) + "%");
  drawLabelValue(5, "Sichweite:", String(visibility) + "m");
}

int windDegTo16(float deg) {
	float x = deg + 11.25f;
	return ((int) (x / 22) % 16);
}

void drawLabelValue(uint8_t line, String label, String value) {
  const uint8_t labelX = 15;
  const uint8_t valueX = 150;
  const uint8_t offsetY = 150;
  gfx.setTextAlignment(TEXT_ALIGN_LEFT);
  gfx.setColor(MINI_YELLOW);
  gfx.drawString(labelX, offsetY + line * 15, label);
  gfx.setColor(MINI_WHITE);
  gfx.drawString(valueX, offsetY + line * 15, value);
}

int8_t getWifiQuality() {
  int32_t dbm = WiFi.RSSI();
  if(dbm <= -100) {
      return 0;
  } else if(dbm >= -50) {
      return 100;
  } else {
      return 2 * (dbm + 100);
  }
}

void drawWifiQuality() {
  int8_t quality = getWifiQuality();
  gfx.setColor(MINI_WHITE);
  for (int8_t i = 0; i < 4; i++) {
    for (int8_t j = 0; j < 2 * (i + 1); j++) {
      if (quality > i * 25 || j == 0) {
        gfx.setPixel(225 + 2 * i, 18 - j);
      }
    }
  }
}

void drawDialog(String text) {
Serial.println(text);

  gfx.fillBuffer(MINI_BLACK);
  gfx.setTransparentColor(MINI_BLACK);
  gfx.setFont(ArialRoundedMTBold_36);
  gfx.setTextAlignment(TEXT_ALIGN_CENTER);
  gfx.setColor(MINI_WHITE);
  gfx.drawString(120, 20, "Weatherman");
  gfx.drawPalettedBitmapFromPgm(240/2 - 64/2, 44, weatherman_logo);
  gfx.setFont(ArialRoundedMTBold_14);
  gfx.drawString(120, 90, "by Jens Marchewka");
  gfx.setColor(MINI_YELLOW);

  gfx.drawString(120, 146, text);
  gfx.commit();
}

void MQTT_connect(bool showDialog = false) {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  char pts[4] = {0};
  int idx = 0;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
      if (showDialog) {
        memset(&pts, 0, 4);
        memset(&pts, '.', idx++ % 4);
        drawDialog(String("Connecting MQTT Broker\n") + String(pts));
      }
    delay(200);  // wait 5 seconds
  }
  Serial.println("MQTT Connected!");
}