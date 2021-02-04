/***************************************************
  Adafruit MQTT Library ESP8266 Example

  Must use ESP8266 Arduino from:
    https://github.com/esp8266/Arduino

  Works great with Adafruit's Huzzah ESP board & Feather
  ----> https://www.adafruit.com/product/2471
  ----> https://www.adafruit.com/products/2821

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Tony DiCola for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/************************* WiFi Access Point *********************************/
#define WLAN_SSID               "Nightlife2.4"
#define WLAN_PASS               "!derm1985"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER              "192.168.2.114"
#define AIO_SERVERPORT          1337                   // use 8883 for SSL
#define AIO_USERNAME            "...your AIO username (see https://accounts.adafruit.com)..."
#define AIO_KEY                 "...your AIO key..."

#define led_built_in_ESP        2
#define led_built_in_Node       16

// Wifi
WiFiClient client;
// MQTT
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
// Pubs
Adafruit_MQTT_Publish photocell = Adafruit_MQTT_Publish(&mqtt, "jens/test/message");
// Subs
Adafruit_MQTT_Subscribe ledNodeSet = Adafruit_MQTT_Subscribe(&mqtt, "/led/set/node");
Adafruit_MQTT_Subscribe ledESPSet = Adafruit_MQTT_Subscribe(&mqtt, "/led/set/esp");

// Build in LEDs
unsigned short led_state_ESP = 1;
unsigned short led_state_Node = 1; 

// last publish millis.
unsigned long lastPublish = 0;

// publish val.
uint32_t x=0;

// SETUP
void setup() {
  pinMode(led_built_in_ESP, OUTPUT);
  pinMode(led_built_in_Node, OUTPUT);
  Serial.begin(115200);
  delay(10);

  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  mqtt.subscribe(&ledNodeSet);
  mqtt.subscribe(&ledESPSet);
}

void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();
  unsigned long elapsedSincePublish = millis() - lastPublish;

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &ledESPSet) {
      Serial.println("LED SET ESP");
      led_state_ESP = atoi((char *)ledESPSet.lastread);
    } else if (subscription == &ledNodeSet) {
      Serial.println("LED SET NODE");
      led_state_Node = atoi((char *)ledNodeSet.lastread);
    }
  }

  handleLedState();

  // Now we can publish stuff!
  if (elapsedSincePublish > 3000) {
    lastPublish = millis();
    Serial.print(F("\nSending photocell val "));
    Serial.print(x);
    Serial.print("...");
    if (! photocell.publish(x++)) {
      Serial.println(F("Failed"));
    } else {
      Serial.println(F("OK!"));
    }
  }

  // ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
  
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }
}

void handleLedState() {
  digitalWrite(led_built_in_ESP, led_state_ESP > 0 ? LOW : HIGH);
  digitalWrite(led_built_in_ESP, led_state_ESP > 0 ? HIGH : LOW);
  digitalWrite(led_built_in_Node, led_state_Node > 0 ? LOW : HIGH);
  digitalWrite(led_built_in_Node, led_state_Node > 0 ? HIGH : LOW);
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}