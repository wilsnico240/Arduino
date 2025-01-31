#include "FastLED.h"
#define LED_DT_1 5 
#define LED_DT_2 6 
#define LED_DT_3 7 
#define LED_CK 11
#define COLOR_ORDER GRB
#define LED_TYPE WS2812
#define NUM_LEDS 300
uint8_t max_bright = 255;
struct CRGB leds[NUM_LEDS];
int currentEffect = 0;
uint8_t    numdots =   4; 
uint8_t   thisfade =   2; 
uint8_t   thisdiff =  16; 
uint8_t    thishue =   0;
uint8_t     curhue =   0; 
uint8_t    thissat = 255; 
uint8_t thisbright = 255; 
uint8_t   thisbeat =   5;
uint8_t thisbeat2 =  23; 
uint8_t thatbeat2 =  28; 
uint8_t thisfade2 =   32; 
uint8_t  thissat2 = 255; 
uint8_t  thisbri2 = 255; 
int        myhue2 =   0;
int    thisdelay2 = 50;
int      twinkrate3 = 100; 
uint8_t  thisdelay3 =  10; 
uint8_t   thisfade3 =   8; 
uint8_t    thishue3 =  50;  
uint8_t    thissat3 = 255; 
uint8_t    thisbri3 = 255; 
bool       randhue3 =   1;  
uint8_t thisdelay4 = 40;  
uint8_t thishue4 = 0;  
int8_t thisrot4 = 1; 
uint8_t deltahue4 = 1;
bool thisdir4 = 0;
CRGBPalette16 currentPalette = CRGBPalette16(CRGB::Black);
CRGBPalette16 targetPalette = RainbowColors_p;  
TBlendType    currentBlending = LINEARBLEND;  
CRGBPalette16 currentPalette2 = RainbowColors_p;
CRGBPalette16 targetPalette2 = ForestColors_p;
CRGBPalette16 targetPalette3;
CRGBPalette16 currentPalette4;
CRGBPalette16 targetPalette4;

void setup() {
Serial.begin(115200);
delay(1000);
LEDS.addLeds<LED_TYPE, LED_DT_1, COLOR_ORDER>(leds, NUM_LEDS);
LEDS.addLeds<LED_TYPE, LED_DT_2, COLOR_ORDER>(leds, NUM_LEDS);
LEDS.addLeds<LED_TYPE, LED_DT_3, COLOR_ORDER>(leds, NUM_LEDS);
FastLED.setBrightness(max_bright); 
FastLED.setMaxPowerInVoltsAndMilliamps(5, 500); 
}

void juggle_pal() { 
curhue = thishue; 
fadeToBlackBy(leds, NUM_LEDS, thisfade);
for( int i = 0; i < numdots; i++) {
leds[beatsin16(thisbeat+i+numdots,0,NUM_LEDS)] += ColorFromPalette(currentPalette, curhue , thisbright, currentBlending); 
curhue += thisdiff;
}} 

void ChangeMe() {  
uint8_t secondHand = (millis() / 1000) % 30;
static uint8_t lastSecond = 99; 
if (lastSecond != secondHand) { 
lastSecond = secondHand;
switch(secondHand) {
case  0: numdots = 1; thisbeat = 20; thisdiff = 16; thisfade = 2; thishue = 0; break; 
case 10: numdots = 4; thisbeat = 10; thisdiff = 16; thisfade = 8; thishue = 128; break;
case 20: numdots = 8; thisbeat =  3; thisdiff =  0; thisfade = 8; thishue=random8(); break; 
case 30: break;
}}} 

void animationA() { 
for (int i = 0; i < NUM_LEDS; i++) {
uint8_t red = (millis() / 5) + (i * 12); 
if (red > 128) red = 0;
leds[i] = ColorFromPalette(currentPalette2, red, red, currentBlending);
}}

void fill_grad() {
uint8_t starthue4 = beatsin8(5, 0, 255);
uint8_t endhue4 = beatsin8(7, 0, 255);
if (starthue4 < endhue4) {
fill_gradient(leds, NUM_LEDS, CHSV(starthue4,255,255), CHSV(endhue4,255,255), FORWARD_HUES);
} 
else {
fill_gradient(leds, NUM_LEDS, CHSV(starthue4,255,255), CHSV(endhue4,255,255), BACKWARD_HUES);
}} 

void sinelon() { 
fadeToBlackBy( leds, NUM_LEDS, thisfade2);
int pos1 = beatsin16(thisbeat2,0,NUM_LEDS);
int pos2 = beatsin16(thatbeat2,0,NUM_LEDS);
leds[(pos1+pos2)/2] += ColorFromPalette(currentPalette, myhue2++, thisbri2, currentBlending);
} 

void twinkle() {
if (random8() < twinkrate3) leds[random16(NUM_LEDS)] += ColorFromPalette(currentPalette4, (randhue3 ? random8() : thishue3), 255, currentBlending);
fadeToBlackBy(leds, NUM_LEDS, thisfade3);
}

void ChangeMe2() { 
uint8_t secondHand2 = (millis() / 1000) % 10; 
static uint8_t lastSecond2 = 99; 
if (lastSecond2 != secondHand2) { 
lastSecond2 = secondHand2;
switch(secondHand2) {
case 0: thisdelay3 = 10; randhue3 = 1; thissat3=255; thisfade3=8; twinkrate3=150; break; 
case 5: thisdelay3 = 100; randhue3 = 0;  thishue3=random8(); thisfade3=2; twinkrate3=20; break;
case 10: break;
}}}

void rainbow_march() { 
if (thisdir4 == 0) thishue4 += thisrot4; else thishue4-= thisrot4; 
fill_rainbow(leds, NUM_LEDS, thishue4, deltahue4); 
}

void ChangeMe3() {  
uint8_t secondHand5 = (millis() / 1000) % 60; 
static uint8_t lastSecond5 = 99;
if (lastSecond5 != secondHand5) { 
lastSecond5 = secondHand5;
switch(secondHand5) {
case  0: thisrot4=1; deltahue4=5; break;
case  5: thisdir4=-1; deltahue4=10; break;
case 10: thisrot4=5; break;
case 15: thisrot4=5; thisdir4=-1; deltahue4=20; break;
case 20: deltahue4=30; break;
case 25: deltahue4=2; thisrot4=5; break;
case 30: break;
}}}

void kerst6() {
ChangeMe3();
EVERY_N_MILLISECONDS(thisdelay4) {   
rainbow_march();
}
FastLED.show();
}

void kerst5() {
ChangeMe2(); 
EVERY_N_MILLISECONDS(100) {
uint8_t maxChanges2 = 24; 
nblendPaletteTowardPalette(currentPalette4, targetPalette4, maxChanges2);
}
EVERY_N_MILLISECONDS(thisdelay3) { 
twinkle();
}
EVERY_N_SECONDS(5) { 
static uint8_t baseC = random8();  
targetPalette4 = CRGBPalette16(CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 192, random8(128,255)), CHSV(random8(), 255, random8(128,255)));
}
FastLED.show();
}

void kerst4() {
EVERY_N_MILLISECONDS(100) {
uint8_t maxChanges = 24; 
nblendPaletteTowardPalette(currentPalette, targetPalette3, maxChanges); 
}
EVERY_N_SECONDS(5) { 
static uint8_t baseC = random8();
targetPalette3 = CRGBPalette16(CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 192, random8(128,255)), CHSV(random8(), 255, random8(128,255)));
}
EVERY_N_MILLISECONDS(thisdelay2) { 
sinelon(); 
}
FastLED.show();
}

void kerst3() {
fill_grad();
FastLED.show(); 
} 

void kerst2() {
EVERY_N_MILLISECONDS(100) {
uint8_t maxChanges = 24; 
nblendPaletteTowardPalette(currentPalette2, targetPalette2, maxChanges); 
}
EVERY_N_SECONDS(5) {  
static uint8_t baseC = random8();
targetPalette2 = CRGBPalette16(CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 192, random8(128,255)), CHSV(random8(), 255, random8(128,255)));
}
animationA(); 
FastLED.show();
}

void kerst1() {
EVERY_N_MILLISECONDS(100) { 
uint8_t maxChanges = 24; 
nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);   
}
ChangeMe();
juggle_pal();
FastLED.show();
}

void loop() {
switch (currentEffect) {
case 0: kerst1(); break; 
case 1: kerst2(); break; 
case 2: kerst3(); break; 
case 3: kerst4(); break; 
case 4: kerst5(); break; 
case 5: kerst6(); break; 
}
if (millis() % (120000) < (50)) { 
currentEffect++;  
if (currentEffect > 5) { 
currentEffect = 0;  
}} }
