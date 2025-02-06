#include "Adafruit_NeoPixel.h"
#define WS2812b_PIN 12
#define WS2812b_PIXELS 64
#define WS2812b_WIDTH 8
#define WS2812b_HEIGHT 8
Adafruit_NeoPixel WS2812b = Adafruit_NeoPixel(WS2812b_PIXELS, WS2812b_PIN, NEO_GRB + NEO_KHZ800);
struct Bubble {
float position; 
float speed;    
uint32_t color; 
bool rising;    
int size;       
bool active;    
};
Bubble bubbles[WS2812b_WIDTH]; 
uint32_t baseLayer[WS2812b_WIDTH]; 

void setup() {
Serial.begin(9600);
WS2812b.begin();
WS2812b.clear();
WS2812b.show();
for (int x = 0; x < WS2812b_WIDTH; x++) {
resetBubble(x);
}
for (int x = 0; x < WS2812b_WIDTH; x++) {
baseLayer[x] = adjustColor(WS2812b.Color(128, 64, 0)); 
}}

void lavaLampEffect() {
delay(100);
WS2812b.clear(); 
for (int x = 0; x < WS2812b_WIDTH; x++) {
if (!bubbles[x].active) {
resetBubble(x); 
}
if (bubbles[x].rising) {
bubbles[x].position -= bubbles[x].speed;
if (bubbles[x].position < 0) {
bubbles[x].position = 0;
bubbles[x].rising = false;
}} 
else {
bubbles[x].position += bubbles[x].speed / 2;
if (bubbles[x].position >= WS2812b_HEIGHT - 1) {
bubbles[x].position = WS2812b_HEIGHT - 1;
bubbles[x].rising = true;
bubbles[x].color = adjustColor(WS2812b.Color(random(128, 256), random(64, 192), 0)); 
}}
float brightness = map(bubbles[x].position, 0, WS2812b_HEIGHT - 1, 100, 10) / 100.0;
uint8_t r = (bubbles[x].color >> 16) & 0xFF;
uint8_t g = (bubbles[x].color >> 8) & 0xFF;
uint8_t b = bubbles[x].color & 0xFF;
r *= brightness;
g *= brightness;
b *= brightness;
drawBubble(x, (int)bubbles[x].position, bubbles[x].size, WS2812b.Color(r, g, b));
}
for (int x = 0; x < WS2812b_WIDTH; x++) {
int pixelIndex = (WS2812b_HEIGHT - 1) * WS2812b_WIDTH + x;
WS2812b.setPixelColor(pixelIndex, baseLayer[x]);
}
for (int i = 0; i < WS2812b_PIXELS; i++) {
uint32_t color = WS2812b.getPixelColor(i);
uint8_t r = (color >> 16) & 0xFF;
uint8_t g = (color >> 8) & 0xFF;
uint8_t b = color & 0xFF;
r = r > 10 ? r - 10 : 0;
g = g > 10 ? g - 10 : 0;
b = b > 10 ? b - 10 : 0;
WS2812b.setPixelColor(i, WS2812b.Color(r, g, b));
}
WS2812b.show(); 
}

void resetBubble(int x) {
bubbles[x].position = WS2812b_HEIGHT - 1; 
bubbles[x].speed = random(5, 15) / 100.0; 
bubbles[x].color = adjustColor(WS2812b.Color(random(128, 256), random(64, 192), 0)); 
bubbles[x].rising = true; 
bubbles[x].size = random(10) < 3 ? 2 : 1; 
bubbles[x].active = true;
}

void drawBubble(int x, int y, int size, uint32_t color) {
if (size == 1) {
int pixelIndex = y * WS2812b_WIDTH + x;
WS2812b.setPixelColor(pixelIndex, color);
} 
else if (size == 2) {
for (int dy = 0; dy < 2; dy++) {
for (int dx = 0; dx < 2; dx++) {
int pixelX = x + dx;
int pixelY = y + dy;
if (pixelX < WS2812b_WIDTH && pixelY < WS2812b_HEIGHT) {
int pixelIndex = pixelY * WS2812b_WIDTH + pixelX;
WS2812b.setPixelColor(pixelIndex, color);
}}}}}

uint32_t adjustColor(uint32_t color) {
uint8_t r = (color >> 16) & 0xFF;
uint8_t g = (color >> 8) & 0xFF;
uint8_t b = color & 0xFF;
g = g * 0.6; 
r = r * 0.8; 
return WS2812b.Color(r, g, b);
}

void loop() {
lavaLampEffect();
}
