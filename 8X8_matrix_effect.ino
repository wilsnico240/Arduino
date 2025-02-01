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

void matrixEffect() {
WS2812b.setBrightness(50);
static int columnHeads[WS2812b_WIDTH] = {-1};
const uint8_t spawnChance = 30;
const uint32_t groen = WS2812b.Color(0, 150, 0);
for(int i=0; i<WS2812b.numPixels(); i++) {
uint32_t kleur = WS2812b.getPixelColor(i);
uint8_t r = (kleur >> 16) & 0xFF;
uint8_t g = (kleur >> 8) & 0xFF;
uint8_t b = kleur & 0xFF;
WS2812b.setPixelColor(i, r*0.7, g*0.7, b*0.7);
}
for(int col=0; col<WS2812b_WIDTH; col++) {
if(columnHeads[col] == -1) {
if(random(255) < spawnChance) {
columnHeads[col] = WS2812b_HEIGHT - 1; 
}
} 
else {
int row = columnHeads[col];
int pixelIndex = row * WS2812b_WIDTH + col;
if(pixelIndex >= 0 && pixelIndex < WS2812b_PIXELS) {
WS2812b.setPixelColor(pixelIndex, groen);
}
for(int i=1; i<=2; i++) {
int trailRow = row + i;
if(trailRow < WS2812b_HEIGHT) {
int trailIndex = trailRow * WS2812b_WIDTH + col;
WS2812b.setPixelColor(trailIndex, groen/(i*2));
}}
columnHeads[col]--;
if(columnHeads[col] < -2) {
columnHeads[col] = -1;
}}}
WS2812b.show();
delay(75);
}

void loop() {
matrixEffect();
}
