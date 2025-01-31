#include "Adafruit_NeoPixel.h"
#include "Adafruit_GFX.h"
#define WS2812b_PIN 5
#define WS2812b_PIXELS 64
#define WS2812b_WIDTH 8
#define WS2812b_HEIGHT 8
Adafruit_NeoPixel WS2812b = Adafruit_NeoPixel(WS2812b_PIXELS, WS2812b_PIN, NEO_GRB + NEO_KHZ800);
float wavePhase = 0.0;
unsigned long prevWaveUpdate = 0;
const float waveSpeed = 0.25;
const float waveFrequency = 1.5;
const float waveAmplitude = 0.54;

void setup () {
Serial.begin(9600);
WS2812b.begin();
WS2812b.clear();
WS2812b.show();
}

void drawSunEffect() {
WS2812b.setBrightness(250);
unsigned long currentMillis = millis();
if (currentMillis - prevWaveUpdate > 50) {
wavePhase += waveSpeed;
if (wavePhase >= 2 * PI) wavePhase -= 2 * PI;
prevWaveUpdate = currentMillis;
}
for (int y = 0; y < WS2812b_HEIGHT; y++) {
for (int x = 0; x < WS2812b_WIDTH; x++) {
float distanceToCenter = sqrt((x - 3.5) * (x - 3.5) + (y - 3.5) * (y - 3.5));
float intensity = 1.0 - (distanceToCenter / 5.0);
intensity = constrain(intensity, 0.0, 1.0);
bool isEdge = (x <= 2 || x >= 5 || y <= 2 || y >= 5);
if (isEdge) {
int depth = 0;
if(x <= 2) depth = 2 - x;  
else if(x >= 5) depth = x - 5; 
if(y <= 2) depth = max(depth, 2 - y); 
else if(y >= 5) depth = max(depth, y - 5);
float phase = wavePhase - depth * waveFrequency;
float wave = (sin(phase) + 1.0) / 2.0;
float modulatedIntensity = intensity * (0.7 + waveAmplitude * wave);
int red = 255 * modulatedIntensity;
int green = 255 * modulatedIntensity * (0.6 - 0.1 * depth/3.0);
int blue = 0;
WS2812b.setPixelColor(y * WS2812b_WIDTH + x, red, green, blue);
}
else {
int red = 255 * intensity;
int green = 255 * intensity * 0.8;
int blue = 0;
WS2812b.setPixelColor(y * WS2812b_WIDTH + x, red, green, blue);
}}}
WS2812b.show();
}

void loop() {
drawSunEffect();
delay(20);
}
