#include "Adafruit_NeoPixel.h"
#include "Adafruit_GFX.h"
#define WS2812b_PIN 12
#define WS2812b_PIXELS 64
#define WS2812b_WIDTH 8
#define WS2812b_HEIGHT 8
Adafruit_NeoPixel WS2812b = Adafruit_NeoPixel(WS2812b_PIXELS,
WS2812b_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
Serial.begin(9600);
WS2812b.begin();
WS2812b.clear();
WS2812b.show();
}

void drawFire() {
WS2812b.setBrightness(75);
for (int y = 0; y < WS2812b_HEIGHT; y++) {
for (int x = 0; x < WS2812b_WIDTH; x++) {
int index = y * WS2812b_WIDTH + x;
int red, green = 25, blue = 0;
if (y == 0) {
red = random(150, 255);
} else if (y < (1 * WS2812b_HEIGHT) - 4) {
red = random(150 + (y * 150) / (2 * WS2812b_HEIGHT / 3), 255);
} else {
if (random(100) < 20) {
red = random(150, 255);
} else {
red = 0;
green = 0;
}}
red += random(-20, 20);
red = constrain(red, 0, 255);
if (y == 7) {
red = (int)(red * 0.10); 
green = (int)(green * 0.10);
} 
else if (y == 6) {
red = (int)(red * 0.25); 
green = (int)(green * 0.25);
} 
else if (y == 5) {
red = (int)(red * 0.50); 
green = (int)(green * 0.50);
}
else if (y == 4) {
red = (int)(red * 0.75); 
green = (int)(green * 0.75);
}
if (y == WS2812b_HEIGHT - 7 && red > 0) {
green = 35; 
}
if (y == WS2812b_HEIGHT - 8 && red > 0) {
green = 75; 
}
WS2812b.setPixelColor(index, WS2812b.Color(red, green, blue));
}}
WS2812b.show();
delay(150);
}

void loop() {
drawFire();
}
