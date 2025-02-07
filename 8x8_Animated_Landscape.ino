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

void animateLandscape() {
delay(200);
static uint8_t cloudPosition = 0; 
cloudPosition = (cloudPosition + 1) % WS2812b_WIDTH;
for (int y = 0; y < WS2812b_HEIGHT - 2; y++) { 
for (int x = 0; x < WS2812b_WIDTH; x++) {
int index = y * WS2812b_WIDTH + x;
WS2812b.setPixelColor(index, WS2812b.Color(0, 0, 128)); 
}}
int sunCenterX = 5; 
int sunCenterY = 2; 
drawCircle(sunCenterX, sunCenterY, 2, WS2812b.Color(255, 223, 0)); 
for (int y = 1; y < 3; y++) { 
for (int x = 0; x < 3; x++) {
int index = y * WS2812b_WIDTH + (x + cloudPosition) % WS2812b_WIDTH;
WS2812b.setPixelColor(index, WS2812b.Color(255, 255, 255)); 
}}
for (int y = WS2812b_HEIGHT - 2; y < WS2812b_HEIGHT; y++) {
for (int x = 0; x < WS2812b_WIDTH; x++) {
int index = y * WS2812b_WIDTH + x;
WS2812b.setPixelColor(index, WS2812b.Color(34, 139, 34)); 
}}
WS2812b.show();
}

void drawCircle(int centerX, int centerY, int radius, uint32_t color) {
for (int y = -radius; y <= radius; y++) {
for (int x = -radius; x <= radius; x++) {
if (x * x + y * y <= radius * radius) { 
int pixelX = centerX + x;
int pixelY = centerY + y;
if (pixelX >= 0 && pixelX < WS2812b_WIDTH && pixelY >= 0 && pixelY < WS2812b_HEIGHT) {
int index = pixelY * WS2812b_WIDTH + pixelX;
WS2812b.setPixelColor(index, color);
}}}}}

void loop() {
animateLandscape();
}
