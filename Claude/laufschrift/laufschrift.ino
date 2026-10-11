// T-OI Plus + WEMOS 8x8 RGB Shield (64x WS2812B-2020)
// Laufschrift "Susanne" von rechts nach links.
// Datenpin D4 = GPIO8, Farbreihenfolge RGB.
//
// Falls die Schrift gespiegelt oder gedreht erscheint, die drei Schalter
// unten (FLIP_X, FLIP_Y, SERPENTINE) anpassen.

#include <Adafruit_NeoPixel.h>

#define DATA_PIN    8
#define NUM_LEDS    64
#define BRIGHTNESS  20
#define SCROLL_MS   110   // Pause pro Spalte (kleiner = schneller)

#define FLIP_X      0     // 1 = links/rechts spiegeln
#define FLIP_Y      0     // 1 = oben/unten spiegeln
#define SERPENTINE  0     // 1 = jede zweite Zeile läuft rückwärts

const char* TEXT = "Susanne";

Adafruit_NeoPixel strip(NUM_LEDS, DATA_PIN, NEO_RGB + NEO_KHZ800);

// 5x7-Schrift (klassischer Font), je 5 Spalten, Bit0 = oberste Zeile
struct Glyph { char c; uint8_t col[5]; };
const Glyph FONT[] = {
  {'S', {0x46, 0x49, 0x49, 0x49, 0x31}},
  {'u', {0x3C, 0x40, 0x40, 0x20, 0x7C}},
  {'s', {0x48, 0x54, 0x54, 0x54, 0x24}},
  {'a', {0x20, 0x54, 0x54, 0x54, 0x78}},
  {'n', {0x7C, 0x08, 0x04, 0x04, 0x78}},
  {'e', {0x38, 0x54, 0x54, 0x54, 0x18}},
};

uint8_t cols[96];   // Spaltenpuffer des ganzen Textes
int numCols = 0;

void buildColumns() {
  numCols = 0;
  for (const char* p = TEXT; *p; p++) {
    for (const Glyph& g : FONT) {
      if (g.c == *p) {
        for (int i = 0; i < 5; i++) cols[numCols++] = g.col[i];
        cols[numCols++] = 0;   // Lücke zwischen Buchstaben
        break;
      }
    }
  }
}

int pixelIndex(int x, int y) {
  if (FLIP_X) x = 7 - x;
  if (FLIP_Y) y = 7 - y;
  if (SERPENTINE && (y & 1)) x = 7 - x;
  return y * 8 + x;
}

void setup() {
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.clear();
  strip.show();
  buildColumns();
}

void loop() {
  uint32_t on = strip.Color(0, 120, 255);
  // offset: -8 = Text beginnt rechts außerhalb, numCols = ganz links raus
  for (int offset = -8; offset <= numCols; offset++) {
    strip.clear();
    for (int x = 0; x < 8; x++) {
      int c = offset + x;
      if (c < 0 || c >= numCols) continue;
      for (int y = 0; y < 8; y++) {
        if (cols[c] & (1 << y)) strip.setPixelColor(pixelIndex(x, y), on);
      }
    }
    strip.show();
    delay(SCROLL_MS);
  }
}
