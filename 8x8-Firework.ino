#include "Adafruit_NeoPixel.h"
#define WS2812b_PIN 12
#define WS2812b_PIXELS 64
#define WS2812b_WIDTH 8
#define WS2812b_HEIGHT 8
Adafruit_NeoPixel WS2812b = Adafruit_NeoPixel(WS2812b_PIXELS, WS2812b_PIN, NEO_GRB + NEO_KHZ800);

struct Particle {
float x;
float y;
float dx;
float dy;
uint32_t color;
int age;
};
int getPixelIndex(int x, int y) {
if(y % 2 == 0) return y * WS2812b_WIDTH + x;
else return y * WS2812b_WIDTH + (WS2812b_WIDTH - 1 - x);
}

void setup() {
Serial.begin(9600);
WS2812b.begin();
WS2812b.setBrightness(50);
WS2812b.clear();
WS2812b.show();
}

void fireworkEffect() {
static unsigned long lastFirework = 0;
static Particle particles[20];
static bool active = false;
for(int i = 0; i < WS2812b_PIXELS; i++) {
uint32_t color = WS2812b.getPixelColor(i);
uint8_t r = (color >> 16) * 0.75;
uint8_t g = (color >> 8) * 0.75;
uint8_t b = color * 0.75;
WS2812b.setPixelColor(i, r, g, b);
}
if(millis() - lastFirework > 4000) {
lastFirework = millis();
active = true;
float angleStep = 2 * PI / 20;
uint16_t baseHue = random(0, 65536);
uint8_t saturation = 200 + random(55);  // Basis verzadiging
uint8_t value = 200 + random(55);       // Basis helderheid
for(int i = 0; i < 20; i++) {
float angle = angleStep * i;
float speed = 0.15 + random(10)/100.0;
uint16_t particleHue = baseHue + random(-1500, 1500);
uint8_t particleSat = constrain(saturation + random(-30, 30), 50, 255);
uint8_t particleVal = constrain(value + random(-30, 30), 50, 255);
particles[i] = {
3.5, 3.5,
cos(angle) * speed,
sin(angle) * speed,
WS2812b.ColorHSV(particleHue, particleSat, particleVal),
25 + random(15)};
}}
if(active) {
active = false;
for(int i = 0; i < 20; i++) {
if(particles[i].age > 0) {
active = true;
particles[i].x += particles[i].dx;
particles[i].y += particles[i].dy;
particles[i].age--;
int x = constrain(particles[i].x, 0, 7);
int y = constrain(particles[i].y, 0, 7);
WS2812b.setPixelColor(getPixelIndex(x,y), particles[i].color);
}}}
WS2812b.show();
delay(30);
}

void loop() {
fireworkEffect();
}
