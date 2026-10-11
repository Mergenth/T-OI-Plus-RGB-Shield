// T-OI Plus + WEMOS 8x8 RGB Shield (64x WS2812B-2020)
// Regenbogen: ein weicher Farbverlauf wandert diagonal ueber die 64 LEDs.
// Datenpin D4 = GPIO8, Farbreihenfolge RGB.

#include <Adafruit_NeoPixel.h>

#define DATA_PIN    8
#define NUM_LEDS    64
#define BRIGHTNESS  20
#define FRAME_MS    30      // Pause pro Bild (kleiner = schneller)
#define HUE_STEP    512     // Farbverschiebung pro Bild (groesser = schneller)
#define HUE_PER_PX  4096    // Farbunterschied zwischen Nachbar-LEDs

Adafruit_NeoPixel strip(NUM_LEDS, DATA_PIN, NEO_RGB + NEO_KHZ800);

uint16_t offsetHue = 0;

void setup() {
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.clear();
  strip.show();
}

void loop() {
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      uint16_t hue = offsetHue + (x + y) * HUE_PER_PX;
      strip.setPixelColor(y * 8 + x, strip.gamma32(strip.ColorHSV(hue, 255, 255)));
    }
  }
  strip.show();
  offsetHue += HUE_STEP;
  delay(FRAME_MS);
}
