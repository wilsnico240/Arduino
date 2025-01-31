#include "Adafruit_NeoPixel.h"
#include "Adafruit_GFX.h"
#define WS2812b_PIN 5
#define WS2812b_PIXELS 64
#define WS2812b_WIDTH 8
#define WS2812b_HEIGHT 8
Adafruit_NeoPixel WS2812b = Adafruit_NeoPixel(WS2812b_PIXELS, WS2812b_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
Serial.begin(9600);
WS2812b.begin();
WS2812b.clear();
WS2812b.show();
}

void drawFire() {
WS2812b.setBrightness(20);
for (int y = 0; y < WS2812b_HEIGHT; y++) {
for (int x = 0; x < WS2812b_WIDTH; x++) {
int index = y * WS2812b_WIDTH + x;
int red, green = 30, blue = 0; 
if (y == 0) { 
red = random(100, 255);
} else if (y < (1 * WS2812b_HEIGHT) - 4) { 
red = random(100 + (y * 150) / (2 * WS2812b_HEIGHT / 3), 255);
} 
else { 
if (random(100) < 20) {
red = random(150, 255);
} else {
red = 0;
green = 0;
}}
red += random(-20, 20);
red = constrain(red, 0, 255);
WS2812b.setPixelColor(index, WS2812b.Color(red, green, blue));
}}
WS2812b.show();
delay(100);
}

void loop() {
drawFire();
}
