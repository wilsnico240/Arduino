#include "Adafruit_NeoPixel.h"
#define WS2812b_PIN 12
#define WS2812b_PIXELS 64
#define WS2812b_WIDTH 8
#define WS2812b_HEIGHT 8
Adafruit_NeoPixel WS2812b = Adafruit_NeoPixel(WS2812b_PIXELS, WS2812b_PIN, NEO_GRB + NEO_KHZ800);

uint8_t roundedDistances[WS2812b_HEIGHT][WS2812b_WIDTH];
int8_t radius = 0; 
enum State { EXPANDING, COLLAPSING, PAUSED };
State currentState = EXPANDING;
unsigned long stateStartTime;
const unsigned long pauseDuration = 1000;
const unsigned long animationInterval = 50;

void setup() {
Serial.begin(9600);
WS2812b.begin();
WS2812b.clear();
WS2812b.show();
for (int y = 0; y < WS2812b_HEIGHT; y++) {
for (int x = 0; x < WS2812b_WIDTH; x++) {
float dx = x - 3.5;
float dy = y - 3.5;
roundedDistances[y][x] = round(sqrt(dx*dx + dy*dy));
}}}

void updateWarpEffect(bool expanding) {
WS2812b.setBrightness(100);
const uint8_t maxRadius = 5;
for (int i = 0; i < WS2812b.numPixels(); i++) {
uint32_t color = WS2812b.getPixelColor(i);
WS2812b.setPixelColor(i, (color & 0xFEFEFE) >> 1);
}
uint8_t fade = (expanding ? radius : (maxRadius - radius)) * 51;
uint8_t red = 255 - fade;
uint8_t green = 255 - fade;
for (int y = 0; y < WS2812b_HEIGHT; y++) {
for (int x = 0; x < WS2812b_WIDTH; x++) {
if (roundedDistances[y][x] == (expanding ? radius : (maxRadius - radius))) {
WS2812b.setPixelColor(y * WS2812b_WIDTH + x, red, green, 255);
}}}
WS2812b.show();
if (expanding) {
if (++radius > maxRadius) {
currentState = COLLAPSING;
radius = 0;
}} 
else {
if (++radius > maxRadius) {
currentState = PAUSED;
radius = 0;
stateStartTime = millis();
}}}

void loop() {
switch(currentState) {
case EXPANDING:
if (millis() - stateStartTime >= animationInterval) {
updateWarpEffect(true); 
stateStartTime = millis();
}
break;
case COLLAPSING:
if (millis() - stateStartTime >= animationInterval) {
updateWarpEffect(false);
stateStartTime = millis();
}
break;
case PAUSED:
if (millis() - stateStartTime >= pauseDuration) {
currentState = EXPANDING;
radius = 0;
}
break;
}}
