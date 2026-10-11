# T-OI-Plus-RGB-Shield

LED-Test fuer das **LILYGO T-OI Plus** (ESP32-C3) mit aufgestecktem **WEMOS 8x8 RGB Shield** (64x WS2812B-2020).

- Sketch: `Claude/rgb_shield/rgb_shield.ino`
- Datenpin des Shields: **D4 = GPIO8** (LILYGO Pinmap V1.3)
- Farbreihenfolge: **RGB** (`NEO_RGB`)
- Zeigt nacheinander Rot, Gruen, Blau, Weiss und ein blaues Lauflicht ueber alle 64 LEDs
- Bibliothek: Adafruit NeoPixel
- GitHub Actions kompiliert den Sketch (`.github/workflows/build.yml`)

## Flashen
Das Board braucht den Download-Modus: **BOOT** gedrueckt halten, kurz **RST** druecken, **BOOT** loslassen.
Nach dem Upload einmal kurz **RST** druecken, damit das Programm startet.
