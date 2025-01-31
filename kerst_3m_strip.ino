#include "FastLED.h"
#define qsubd(x, b) ((x > b) ? b : 0)
#define qsuba(x, b) ((x > b) ? x - b : 0)
#define LED_DT_1 5 
#define LED_DT_2 6 
#define LED_DT_3 7
#define LED_DT_4 8
#define LED_CK 11
#define COLOR_ORDER GRB
#define LED_TYPE WS2812B
#define NUM_LEDS 180
#define maxRipples 6
uint8_t max_bright = 255;
struct CRGB leds[NUM_LEDS];
CRGBPalette16 currentPalette;
CRGBPalette16 targetPalette;
TBlendType currentBlending;
uint8_t speed;
uint8_t loc1;
uint8_t loc2;
uint8_t ran1;
uint8_t ran2;
uint8_t thisfade = 8;
int thishue = 50;
uint8_t thisinc = 1;
uint8_t thissat = 100;
uint8_t thisbri = 255;
int huediff = 256;
uint8_t thisdelay = 5;
unsigned int ledLoc = 0;
int currentEffect = 0;
struct ripple {
uint8_t brightness;
int8_t color;
int16_t pos;
int8_t velocity;
uint8_t life;
uint8_t maxLife;
uint8_t fade;
bool exist;
void Move() {
pos += velocity; 
life++;
if (pos > NUM_LEDS - 1) {
velocity *= -1; 
pos = NUM_LEDS - 1; 
}
if (pos < 0) { 
velocity *= -1; 
pos = 0; 
}
brightness = scale8(brightness, fade);
if (life > maxLife) exist = false; 
}
void Init(uint8_t Fade, uint8_t MaxLife) {
pos = random8(NUM_LEDS / 8, NUM_LEDS - NUM_LEDS / 8);
velocity = 1; 
life = 0; 
maxLife = MaxLife; 
exist = true; 
brightness = 255; 
color = millis(); 
fade = Fade; 
}};
typedef struct ripple Ripple;
Ripple ripples[maxRipples];

void setup() {
Serial.begin(115200);
delay(1000);
LEDS.addLeds<LED_TYPE, LED_DT_1, COLOR_ORDER>(leds, NUM_LEDS);
LEDS.addLeds<LED_TYPE, LED_DT_2, COLOR_ORDER>(leds, NUM_LEDS);
LEDS.addLeds<LED_TYPE, LED_DT_3, COLOR_ORDER>(leds, NUM_LEDS);
LEDS.addLeds<LED_TYPE, LED_DT_4, COLOR_ORDER>(leds, NUM_LEDS); 
currentBlending = LINEARBLEND; 
currentPalette = PartyColors_p; 
FastLED.setBrightness(max_bright); 
FastLED.setMaxPowerInVoltsAndMilliamps(5, 500); 
}

void confetti_pal() {
fadeToBlackBy(leds, NUM_LEDS, thisfade);
int pos = random16(NUM_LEDS);
leds[pos] = ColorFromPalette(currentPalette, thishue + random16(huediff) / 4, thisbri, currentBlending);
thishue += thisinc;
}

void ChangeMe() {
uint8_t secondHand = (millis() / 1000) % 15; 
static uint8_t lastSecond = 99;
if (lastSecond != secondHand) {
lastSecond = secondHand;
switch (secondHand) {
case 0:
targetPalette = OceanColors_p; 
thisinc=1; 
thishue=192; 
thissat=255; 
thisfade=2; 
huediff=255; 
break;
case 5:
targetPalette = LavaColors_p; 
thisinc=2; 
thishue=128; 
thisfade=8; 
huediff=64; 
break;
case 10:
targetPalette = ForestColors_p; 
thisinc=1; 
thishue=random16(255); 
thisfade=1; 
huediff=16; 
break;
case 15: break;
}}}

void rainbow_march(uint8_t delayTime, uint8_t deltahue) {
uint8_t hueValue = millis() * (255 - delayTime) / 255; 
fill_rainbow(leds, NUM_LEDS, hueValue, deltahue);
}

void rippless() {
for (int i = 0; i < maxRipples; i += 2) { 
if (random8() > 224 && !ripples[i].exist) { 
ripples[i].Init(192, 10); 
ripples[i + 1] = ripples[i];
ripples[i + 1].velocity *= -1; 
}}
for (int i = 0; i < maxRipples; i++) { 
if (ripples[i].exist) {
leds[ripples[i].pos] = ColorFromPalette(currentPalette, ripples[i].color, ripples[i].brightness, LINEARBLEND);
ripples[i].Move();
}}
fadeToBlackBy(leds, NUM_LEDS, 160);
} 

void SetupMySimilar4Palette() { 
uint8_t thishue = random8();
targetPalette = CRGBPalette16(CHSV(thishue+random8(32), 255, random8(128,255)),
CHSV(thishue+random8(32), 255, random8(192,255)),
CHSV(thishue+random8(32), 192, random8(192,255)),
CHSV(thishue+random8(32), 255, random8(128,255)));
} 

void E6() {
rainbow_march(200, 10);
}

void E5() {
ChangeMe();
EVERY_N_MILLISECONDS(100) {
uint8_t maxChanges = 24; 
nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges); 
}
EVERY_N_MILLISECONDS(thisdelay) { 
confetti_pal(); 
}}

void E4() {
uint8_t blurAmount = dim8_raw(beatsin8(3,64,192)); 
blur1d(leds, NUM_LEDS, blurAmount); 
uint8_t i = beatsin8(9, 0, NUM_LEDS); 
uint8_t j = beatsin8(7, 0, NUM_LEDS); 
uint8_t k = beatsin8(5, 0, NUM_LEDS); 
uint16_t ms = millis(); 
leds[(i + j) / 2] = CHSV(ms / 29, 200, 255); 
leds[(j + k) / 2] = CHSV(ms / 41, 200, 255); 
leds[(k + i) / 2] = CHSV(ms / 73, 200, 255); 
leds[(k + i + j) / 3] = CHSV(ms /53 ,200 ,255);  
}

void E3() {
EVERY_N_MILLISECONDS(50) {  
uint8_t maxChanges = 24; 
nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);  
}
EVERY_N_SECONDS(5) {
SetupMySimilar4Palette();
}
EVERY_N_MILLIS(50) {  
rippless(); 
}} 

void E2() {
speed = beatsin8(6,0 ,255); 
CRGB clr1 = blend(CHSV(beatsin8(3 ,0 ,255),255 ,255), CHSV(beatsin8(4 ,0 ,255),255 ,255), speed);  
CRGB clr2 = blend(CHSV(beatsin8(4 ,0 ,255),255 ,255), CHSV(beatsin8(3 ,0 ,255),255 ,255), speed); 
loc1 = beatsin8(10 ,0 ,NUM_LEDS -1); 
fill_gradient_RGB(leds ,0 ,clr2 ,loc1 ,clr1);  
fill_gradient_RGB(leds ,loc1 ,clr2 ,NUM_LEDS -1 ,clr1);  
}

void E1() {
EVERY_N_MILLIS_I(thisTimer,100) {  
uint8_t timeval=beatsin8(10 ,5 ,100);
thisTimer.setPeriod(timeval);
ledLoc=(ledLoc+1) % (NUM_LEDS-1);
leds[ledLoc]=ColorFromPalette(currentPalette ,ledLoc ,255,currentBlending);
}
fadeToBlackBy(leds ,NUM_LEDS ,thisfade);
}

void loop() {
switch (currentEffect) {
case 0: E1(); break; 
case 1: E2(); break; 
case 2: E3(); break; 
case 3: E4(); break; 
case 4: E5(); break; 
case 5: E6(); break; 
}
if (millis() % (60000) < (50)) { 
currentEffect++;  
if (currentEffect > 5) { 
currentEffect = 0;  
}} 
FastLED.show();
}
