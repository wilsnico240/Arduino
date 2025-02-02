#include "Adafruit_NeoPixel.h"
#define WS2812b_PIN 12
#define WS2812b_PIXELS 64
#define WS2812b_WIDTH 8
#define WS2812b_HEIGHT 8
#define PACMAN_CENTER_X 2
#define PACMAN_CENTER_Y 3
#define PACMAN_RADIUS 2.8
#define ANIMATION_SPEED 75
#define DOT_SPACING 2 
#define MAX_DOTS 3 
Adafruit_NeoPixel WS2812b = Adafruit_NeoPixel(WS2812b_PIXELS, WS2812b_PIN, NEO_GRB + NEO_KHZ800);

uint32_t buffer[WS2812b_PIXELS];
bool pixelChanged[WS2812b_PIXELS] = {false};
int getPixelIndex(int x, int y) {
return y * WS2812b_WIDTH + x;
}

void setup() {
Serial.begin(9600);
WS2812b.begin();
WS2812b.clear();
WS2812b.show();
memset(buffer, 0, sizeof(buffer));
}

void animatePacMan() {
WS2812b.setBrightness(100);
static int mouthAngle = 0;
static int animationDirection = 1;
static unsigned long previousMillis = 0;
static int dots[MAX_DOTS] = {-1, -1, -1};
static int spawnCounter = 0;
if (millis() - previousMillis >= ANIMATION_SPEED) {
previousMillis = millis();
mouthAngle += animationDirection * 15;
if (mouthAngle >= 60 || mouthAngle <= 0) {
animationDirection *= -1;
}
bool mouthClosed = (mouthAngle == 0);
if (mouthClosed) {
for (int i = 0; i < MAX_DOTS; i++) {
if (dots[i] != -1) {
dots[i]--; 
if (dots[i] <= PACMAN_CENTER_X) dots[i] = -1;
}}}
if (++spawnCounter >= DOT_SPACING) {
for (int i = 0; i < MAX_DOTS; i++) {
if (dots[i] == -1) {
bool spaceAvailable = true;
for (int j = 0; j < MAX_DOTS; j++) {
if (dots[j] >= WS2812b_WIDTH - DOT_SPACING) {
spaceAvailable = false;
break;
}}
if (spaceAvailable) {
dots[i] = WS2812b_WIDTH - 1;
break;
}}}
spawnCounter = 0;
}
memset(buffer, 0, sizeof(buffer));
memset(pixelChanged, false, sizeof(pixelChanged));
for (int i = 0; i < MAX_DOTS; i++) {
if (dots[i] != -1) {
int index = getPixelIndex(dots[i], PACMAN_CENTER_Y);
buffer[index] = WS2812b.Color(0, 200, 255);
pixelChanged[index] = true;
if (dots[i] < WS2812b_WIDTH - 1) {
int spaceIndex = getPixelIndex(dots[i] + 1, PACMAN_CENTER_Y);
buffer[spaceIndex] = 0;
pixelChanged[spaceIndex] = true;
}}}
for (int y = 0; y < WS2812b_HEIGHT; y++) {
for (int x = 0; x < WS2812b_WIDTH; x++) {
int index = getPixelIndex(x, y);
float dx = x - PACMAN_CENTER_X;
float dy = y - PACMAN_CENTER_Y;
float distance = sqrt(dx*dx + dy*dy);
if (distance <= PACMAN_RADIUS) {
float angle = atan2(dy, dx) * 180.0 / PI;
bool inMouth = false;
if (mouthAngle > 0) {
inMouth = (angle > -mouthAngle && angle < mouthAngle);
}
if (!inMouth) {
buffer[index] = WS2812b.Color(255, 255, 0);
} 
else {
buffer[index] = 0;
}
pixelChanged[index] = true;
}}}
for (int i = 0; i < WS2812b_PIXELS; i++) {
if (pixelChanged[i]) {
WS2812b.setPixelColor(i, buffer[i]);
}}
WS2812b.show();
}}

void loop() {
animatePacMan();
}
