// Example of drawing a graphical "switch" and using
// the touch screen to change it's state.

// This sketch does not use the libraries button drawing
// and handling functions.

// Based on Adafruit_GFX library onoffbutton example.

// Touch handling for XPT2046 based screens is handled by
// the TFT_eSPI library.

// Calibration data is stored in SPIFFS so we need to include it
#include "FS.h"

#include <SPI.h>

#include <TFT_eSPI.h> // Hardware-specific library

#include "JWifiSetup.h"

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

// This is the file name used to store the touch coordinate
// calibration data. Cahnge the name to start a new calibration.
#define CALIBRATION_FILE "/TouchCalData3"

// Set REPEAT_CAL to true instead of false to run calibration
// again, otherwise it will only be done once.
// Repeat calibration if you change the screen rotation.
#define REPEAT_CAL true

boolean SwitchOn = false;

// Comment out to stop drawing black spots
#define BLACK_SPOT

// Switch position and size
#define FRAME_X 100
#define FRAME_Y 64
#define FRAME_W 120
#define FRAME_H 50

// Red zone size
#define REDBUTTON_X FRAME_X
#define REDBUTTON_Y FRAME_Y
#define REDBUTTON_W (FRAME_W/2)
#define REDBUTTON_H FRAME_H

// Green zone size
#define GREENBUTTON_X (REDBUTTON_X + REDBUTTON_W)
#define GREENBUTTON_Y FRAME_Y
#define GREENBUTTON_W (FRAME_W/2)
#define GREENBUTTON_H FRAME_H


JWifiSetup wifiSetup("/wificonf", "WeatherManHotspot", "weatherman");

//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
void setup(void)
{
  Serial.begin(115200);
  while(! Serial) ;
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLUE);

  JWifiData* dat = wifiSetup.GetWifi();
  Serial.println("Aquired Wifi data...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(dat->ssid, dat->passwd);  
  Serial.println("Connecting Wifi");
    // Wait for connection
  uint16_t waits = 0;
  int status;
  while ((status = WiFi.status()) != WL_CONNECTED) {
    if (waits > 200) {
      wifiSetup.RemoveWifiConfig();
      Serial.println("wrong credentials, remove config and restart.");
      exit(1);
    }
    delay(500);
    Serial.print(".");   
    waits++;
  }
  Serial.println("");
  Serial.println("Wifi Connected.");
}
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
void loop()
{
  
}