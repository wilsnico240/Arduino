#include "Adafruit_NeoPixel.h"
#define WS2812b_PIN 12
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

void softStarrySkyEffect() {
static uint8_t hue = 0;
for (int i = 0; i < WS2812b_PIXELS; i++) {
if (random(100) < 5) { 
uint32_t color = WS2812b.ColorHSV((hue + random(0, 65536)) % 65536, 255, random(50, 150));
WS2812b.setPixelColor(i, color);
} 
else {
WS2812b.setPixelColor(i, 0); 
}}
WS2812b.show(); 
delay(150); 
  hue = (hue + 1) % 256;
}

void loop() {
softStarrySkyEffect();
}
