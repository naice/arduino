
#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>
FASTLED_USING_NAMESPACE

#define LED                       3
#define LED_COUNT                 8


uint8_t max_bright = 255; 
uint8_t hue = 0; 

CRGB leds[LED_COUNT];

void setup() {
  FastLED.addLeds<WS2812, LED, GRB>(leds, LED_COUNT)
        .setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(max_bright);
  Serial.begin(9600);
  testIntro();
  FastLED.clear();
  FastLED.show();
  delay(1000);
}
void myDelay(unsigned long ms) {              // ms: duration
    unsigned long start = millis();           // start: timestamp
    for (;;) {
        unsigned long now = millis();         // now: timestamp
        unsigned long elapsed = now - start;  // elapsed: duration
        if (elapsed >= ms)                    // comparing durations: OK
            return;
    }
}
void loop() {
    EVERY_N_MILLISECONDS(10) {
      sin1();
      FastLED.show();
    }
}

void testIntro() {

    for (int i = 0; i < LED_COUNT; i++) {
      leds[i] = CRGB (255, 0, 0);
      FastLED.show();
      delay(40);
    }
    for (int i = 0; i < LED_COUNT; i++) {
      leds[i] = CRGB (0, 0, 0);
      FastLED.show();
      delay(40);
    }

    for (int i = 0; i < LED_COUNT; i++) {
      leds[i] = CRGB (0, 255, 0);
      FastLED.show();
      delay(40);
    }
    for (int i = 0; i < LED_COUNT; i++) {
      leds[i] = CRGB (0, 0, 0);
      FastLED.show();
      delay(40);
    }

    for (int i = 0; i < LED_COUNT; i++) {
      leds[i] = CRGB (0, 0, 255);
      FastLED.show();
      delay(40);
    }
    for (int i = 0; i < LED_COUNT; i++) {
      leds[i] = CRGB (0, 0, 0);
      FastLED.show();
      delay(40);
    }

    delay(100);

}

void sin() {  
  hue++;
  fadeToBlackBy(leds, LED_COUNT, 20);
  int pos = beatsin16(13,0,LED_COUNT-1);
  leds[pos] = CHSV(160, 255, 192);
}
void sin1() {  
  fadeToBlackBy(leds, LED_COUNT, 20);
  int pos = LED_COUNT-beatsin16(14,0,LED_COUNT-1)-1;
  leds[pos] = CHSV(210, 255, 192);
  pos = beatsin16(21,0,LED_COUNT-1);
  leds[pos] = CHSV(190, 255, 192);
  pos = beatsin16(25,0,LED_COUNT-1);
  leds[pos] = CHSV(300, 255, 192);
}