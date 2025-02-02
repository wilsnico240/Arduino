#include "Adafruit_NeoPixel.h"
#define WS2812b_PIN 12
#define WS2812b_PIXELS 64
#define WS2812b_WIDTH 8
#define WS2812b_HEIGHT 8
Adafruit_NeoPixel WS2812b = Adafruit_NeoPixel(WS2812b_PIXELS, WS2812b_PIN, NEO_GRB + NEO_KHZ800);

struct Band {
float current;
float target;
unsigned long lastChange;
unsigned long changeInterval;
};
Band bands[8];
unsigned long lastBeatTime = 0;
const unsigned long beatInterval = 500;

void setup() {
Serial.begin(9600);
WS2812b.begin();
WS2812b.clear();
WS2812b.show();
for (int i = 0; i < 8; i++) {
bands[i].current = 0;
bands[i].target = 0;
bands[i].lastChange = 0;
bands[i].changeInterval = (i >= 6) ? random(300, 600) : random(50, 200);
}}

void visualizeEqualizer() {
WS2812b.setBrightness(100);
unsigned long now = millis();
if (now - lastBeatTime >= beatInterval) {
lastBeatTime = now;
for (int i = 6; i < 8; i++) { 
bands[i].target = 8; 
bands[i].lastChange = now;
bands[i].changeInterval = 100; 
}}
for (int i = 0; i < 8; i++) {
if (now - bands[i].lastChange > bands[i].changeInterval) {
if (i >= 6) { 
bands[i].target = random(4, 7); 
bands[i].changeInterval = random(300, 600);
}
else if (i == 5) { 
bands[i].target = random(4, 6); 
bands[i].changeInterval = random(300, 600);
}
else if (i == 4) { 
bands[i].target = random(2, 6);
bands[i].changeInterval = random(50, 150);
}
else if (i == 3) { 
bands[i].target = random(2, 5);
bands[i].changeInterval = random(50, 150);
}
else if (i == 2) { 
bands[i].target = random(2, 5); 
bands[i].changeInterval = random(50, 150);
}
else {
bands[i].target = random(1, 6); 
bands[i].changeInterval = random(50, 150);
}
bands[i].lastChange = now;
}
float delta = bands[i].target - bands[i].current;
bands[i].current += delta * 0.2;
bands[i].current = constrain(bands[i].current, 0, 8);
}
WS2812b.clear();
for (int c = 0; c < 8; c++) {
int l = round(bands[c].current);
l = constrain(l, 0, 8);
for (int j = 0; j < l; j++) {
int row = j; 
int column = c; 
int index = row * WS2812b_WIDTH + column;
if (c >= 5) { 
if (row >= 5) {
WS2812b.setPixelColor(index, WS2812b.Color(255, 0, 0)); 
} 
else if (row >= 3) {
WS2812b.setPixelColor(index, WS2812b.Color(255, 255, 0));
} 
else {
WS2812b.setPixelColor(index, WS2812b.Color(0, 255, 0)); 
}} 
else { 
if (row >= 5) { 
WS2812b.setPixelColor(index, WS2812b.Color(200, 200, 0));
} 
else if (row >= 3) {
WS2812b.setPixelColor(index, WS2812b.Color(150, 150, 0));
} 
else {
WS2812b.setPixelColor(index, WS2812b.Color(0, 150, 0));
}}}}
WS2812b.show();
delay(10);
}

void loop() {
visualizeEqualizer();
}
