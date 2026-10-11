// LILYGO T-OI Plus (ESP32-C3) + WEMOS 8x8 RGB Shield (64x WS2812B-2020)
// Farbtest: rot, gruen, blau, weiss, danach Lauflicht ueber alle 64 LEDs.
// Shield-Datenpin D4 = GPIO8 (laut LILYGO-Pinmap V1.3), Farbreihenfolge RGB
#include <Adafruit_NeoPixel.h>

#define DATA_PIN   8
#define NUM_LEDS   64
#define BRIGHTNESS 20   // niedrig halten (max 255), USB-Strom schonen

Adafruit_NeoPixel strip(NUM_LEDS, DATA_PIN, NEO_RGB + NEO_KHZ800);

void fillAll(uint32_t color, int ms) {
  strip.fill(color);
  strip.show();
  delay(ms);
}

void setup() {
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.clear();
  strip.show();
}

void loop() {
  fillAll(strip.Color(255, 0, 0), 500);     // rot
  fillAll(strip.Color(0, 255, 0), 500);     // gruen
  fillAll(strip.Color(0, 0, 255), 500);     // blau
  fillAll(strip.Color(255, 255, 255), 500); // weiss
  strip.clear();
  strip.show();
  for (int i = 0; i < NUM_LEDS; i++) {      // Lauflicht ueber alle 64 LEDs
    strip.setPixelColor(i, strip.Color(0, 120, 255));
    strip.show();
    delay(25);
  }
  delay(300);
}
