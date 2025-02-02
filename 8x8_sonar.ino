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

void radarAnimation() {
static float angle = 0;
static float angleStep = 3;
static bool detectActive = false;
static float detectAngle = 0;
static int detectRadius = 0;
static int detectBrightness = 0;
const int fadeAmount = 2; 
if (detectActive) {
detectBrightness = max(detectBrightness - fadeAmount, 0);
if (detectBrightness == 0) detectActive = false;
}
WS2812b.clear();
float rad = radians(angle);
for (float r = 0; r < 8; r += 0.3) {
float thickness = map(r, 0, 8, 0.3, 1.5);
for (float t = -thickness; t <= thickness; t += 0.5) {
float offsetAngle = rad + t * (0.05 + r/80);
int x = round(3.5 + r * cos(offsetAngle));
int y = round(3.5 + r * sin(offsetAngle));
if (x >= 0 && x < 8 && y >= 0 && y < 8) {
int idx = y * 8 + x;
int greenIntensity = 40 + 215 * (1 - r/8);
int blueComponent = 20 * (r/8);
WS2812b.setPixelColor(idx, WS2812b.Color(0, greenIntensity * (1 - abs(t/thickness)), blueComponent));
}}}
for (float r = 6; r < 8; r += 0.5) {
int x = round(3.5 + r * cos(rad));
int y = round(3.5 + r * sin(rad));
if (x >= 0 && x < 8 && y >= 0 && y < 8) {
int idx = y * 8 + x;
WS2812b.setPixelColor(idx, WS2812b.Color(0, 30, 10));
}}
if (detectActive) {
float detectRad = radians(detectAngle);
int dx = round(3.5 + detectRadius * cos(detectRad));
int dy = round(3.5 + detectRadius * sin(detectRad));
if (dx >= 0 && dx < 8 && dy >= 0 && dy < 8) {
int idx = dy * 8 + dx;
int baseGlow = 15; 
WS2812b.setPixelColor(idx, WS2812b.Color(
baseGlow + detectBrightness, 0, 0));
}}
angle += angleStep;
if (angle >= 360) angle -= 360;
if (random(0, 200) == 0) {
detectActive = true;
detectBrightness = 50;
detectAngle = angle;
detectRadius = random(3, 7);
}
WS2812b.show();
delay(20);
}

void loop() {
radarAnimation();
}
