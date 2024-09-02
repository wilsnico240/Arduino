#include <U8g2lib.h>
#include <Wire.h>
#include <WiFiS3.h>
#include "WiFiSSLClient.h"
#include "IPAddress.h"
#include <ArduinoJson.h>
#include <assert.h>
#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"
#include "animation.h"
#include "animation2.h"
#include "bodje.h"
#include "hello.h"
#include "over.h"
#include "over2.h"
#include "image0.h"
#include "image1.h"
#include "image2.h"
#include "image3.h"
#include "image4.h"
#include "image5.h"
#include "image6.h"
#include "image7.h"
#include "image8.h"
#include "image9.h"
#include "flappy1.h"
#include "firework6.h"
#include "firework11.h"
#include "firework15.h"
#include "firework21.h"
#include "firework23.h"
#include "firework26.h"
#include "firework30.h"
#include "firework34.h"
#include "firework36.h"
#include "snake1.h"
#include "skynet.h"
#include <FastLED.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <RTC.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include <Adafruit_BMP085_U.h>
#include <Adafruit_Sensor.h>
#include <MQSpaceData.h>
#include <DHT.h>
#define DHTPIN 13
#define DHTTYPE DHT22
#define ADC_BIT_RESU 10
#define space A2
MQSpaceData MQ(ADC_BIT_RESU, space);
#define DATA_PIN 5   
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define NUM_ROWS 16
#define NUM_COLS 16
#define NUM_LEDS NUM_ROWS * NUM_COLS
#define BRIGHTNESS  100
#define BRIGHTNESS2 200
#define BRIGHTNESS3 200
#define MAX_POWER_MILLIAMPS 400 
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0
#define SW 4
#define texSizeX 16
#define texSizeY 16
#define image_width 128
#define image_height 21
Adafruit_8x16matrix matrix2 = Adafruit_8x16matrix();
DHT dht(DHTPIN, DHTTYPE);
char server2[] = "v2.jokeapi.dev";
WiFiSSLClient clientssl;
WiFiClient client;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "be.pool.ntp.org");
U8G2_SH1107_SEEED_128X128_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
CRGB leds2[NUM_LEDS];
CRGB leds[NUM_LEDS];
byte dist [NUM_LEDS];
byte ang  [NUM_LEDS];
byte bump[(NUM_COLS+2)*(NUM_ROWS+2)];
CRGB chsvLut[256];
CRGB tex  [16][16];
DEFINE_GRADIENT_PALETTE(firepal) { 
0,  0,  0,  0, 
255,  126,  34,  0, 
255,  0,  0,  0 
};
CRGBPalette16 myPal = firepal;
DEFINE_GRADIENT_PALETTE(firepal2) { 
0,  0,  0,  0,
255,  255,  0,  0,
200,  200,  150,  0,
255,  255,  255,  255
};
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);
ArduinoLEDMatrix matrix;
char ssid[] = "--------";
char pass[] = "--------";
char server[] = "api.open-meteo.com";
char* weekday[7] = { "Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi" };
char* month[12] = {"Decembre", "Janvier", "Fevrier", "Mars", "Avril", "Mai", "Juin", "Juillet", "Aout", "Septembre", "Octobre", "Novembre"};
const int sensorPin = A3;
const int green_led = 8;
const int orange_led = 7;
const int red_led = 6;
const int RPin = 2;
const uint32_t heart[] = {
0x3184a444,
0x44042081,
0x100a0040
};
int startDayOfWeek(int y, int m, int d){
static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
y -= m < 3;
return (y +y/4 -y/100 + y/400 + t[m-1] + d)% 7; 
} 
int startDay = 0;
String week1 ="";
String week2 ="";
String week3 ="";
String week4 ="";
String week5 ="";
int newWeekStart = 0;
char monthString2[37]= {"JanFevMarAvrMaiJuiJuiAouSepOctNovDec"};
int  monthIndex2[122] ={0,3,6,9,12,15,18,21,24,27,30,33};
char monthName2[3]="";
int monthLength = 0;
int sensorValue2;
long sum = 0;
int vout = 0;
int uv = 0;
int elevation = 0;
int temperature = 0;
int windspeed = 0;
int humidity = 0;
int pressuresea = 0;
int pressure = 0;
int winddirection = 0;
int windgusts = 0;
unsigned long lastConnectionTime = 0;
const unsigned long postingInterval = 10L * 1000L;
unsigned long lastConnectionTime2 = 0;
const unsigned long postingInterval2 = 278L * 1000L;
unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0;
const long interval = 60000;
const long interval2 = 300000;
int x, Air;
String xname, mode, strper;
int RState = LOW;
int status = WL_IDLE_STATUS;
int joystick_pos = 0;
int joystick_pos2 = 0;
int joystick_pos3 = 0;
int tempo = 80;
int tempo2 = 105;
int buzzer = 3;
int melody[] = {
NOTE_D4, -8, NOTE_G4, 16, NOTE_C5, -4,
NOTE_B4, 8, NOTE_G4, -16, NOTE_E4, -16, NOTE_A4, -16,
NOTE_D5, 2,
};
int notes = sizeof(melody) / sizeof(melody[0]) / 2;
int wholenote = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;
int line_pos, line_height, player_pos;
bool sw_state;
uint8_t ledBrightness = 10;
uint16_t getIndex(uint16_t x, uint16_t y){
uint16_t index;
if (y == 0){
index = x;
}
else if (y % 2 == 0){
index = y * NUM_COLS + x;
}
else{
index = ((y * NUM_COLS) + (NUM_COLS-1)) - x;
}
return index;
}
uint8_t XY (uint8_t x, uint8_t y) {
const uint8_t XYTable[] = {
255, 254, 253, 252, 251, 250, 249, 248, 247, 246, 245, 244, 243, 242, 241, 240,
224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
223, 222, 221, 220, 219, 218, 217, 216, 215, 214, 213, 212, 211, 210, 209, 208,
192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
191, 190, 189, 188, 187, 186, 185, 184, 183, 182, 181, 180, 179, 178, 177, 176,
160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175,
159, 158, 157, 156, 155, 154, 153, 152, 151, 150, 149, 148, 147, 146, 145, 144,
128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,
127, 126, 125, 124, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 113, 112,
96,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
95,  94,  93,  92,  91,  90,  89,  88,  87,  86,  85,  84,  83,  82,  81,  80,
64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,
63,  62,  61,  60,  59,  58,  57,  56,  55,  54,  53,  52,  51,  50,  49,  48,
32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,
31,  30,  29,  28,  27,  26,  25,  24,  23,  22,  21,  20,  19,  18,  17,  16,
0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15};
uint8_t i = (y * NUM_COLS) + x;
uint8_t j = XYTable[i];
return j;
}
uint8_t frame[8][12] = {
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};
byte frame2[8][12];
byte flatFrame[8 * 12];
struct Point {
byte x;
byte y;
};
Point snake[100];
int snakeLength = 3;
Point food;
int direction = 0; 
void draw_line(int length, int x) {
if (x > 11)
return;
for (int i = 0; i < length; i++) {
if (7 - i <= 0)
return;
frame[7 - i][x] = 1;
}}

void clearscreen() {
frame[0][0] = 0;
frame[0][1] = 0;
frame[0][2] = 0;
frame[0][3] = 0;
frame[0][4] = 0;
frame[0][5] = 0;
frame[0][6] = 0;
frame[0][7] = 0;
frame[0][8] = 0;
frame[0][9] = 0;
frame[0][10] = 0;
frame[0][11] = 0;
frame[1][0] = 0;
frame[1][1] = 0;
frame[1][2] = 0;
frame[1][3] = 0;
frame[1][4] = 0;
frame[1][5] = 0;
frame[1][6] = 0;
frame[1][7] = 0;
frame[1][8] = 0;
frame[1][9] = 0;
frame[1][10] = 0;
frame[1][11] = 0;
frame[2][0] = 0;
frame[2][1] = 0;
frame[2][2] = 0;
frame[2][3] = 0;
frame[2][4] = 0;
frame[2][5] = 0;
frame[2][6] = 0;
frame[2][7] = 0;
frame[2][8] = 0;
frame[2][9] = 0;
frame[2][10] = 0;
frame[2][11] = 0;
frame[3][0] = 0;
frame[3][1] = 0;
frame[3][2] = 0;
frame[3][3] = 0;
frame[3][4] = 0;
frame[3][5] = 0;
frame[3][6] = 0;
frame[3][7] = 0;
frame[3][8] = 0;
frame[3][9] = 0;
frame[3][10] = 0;
frame[3][11] = 0;
frame[4][0] = 0;
frame[4][1] = 0;
frame[4][2] = 0;
frame[4][3] = 0;
frame[4][4] = 0;
frame[4][5] = 0;
frame[4][6] = 0;
frame[4][7] = 0;
frame[4][8] = 0;
frame[4][9] = 0;
frame[4][10] = 0;
frame[4][11] = 0;
frame[5][0] = 0;
frame[5][1] = 0;
frame[5][2] = 0;
frame[5][3] = 0;
frame[5][4] = 0;
frame[5][5] = 0;
frame[5][6] = 0;
frame[5][7] = 0;
frame[5][8] = 0;
frame[5][9] = 0;
frame[5][10] = 0;
frame[5][11] = 0;
frame[6][0] = 0;
frame[6][1] = 0;
frame[6][2] = 0;
frame[6][3] = 0;
frame[6][4] = 0;
frame[6][5] = 0;
frame[6][6] = 0;
frame[6][7] = 0;
frame[6][8] = 0;
frame[6][9] = 0;
frame[6][10] = 0;
frame[6][11] = 0;
frame[7][0] = 0;
frame[7][1] = 0;
frame[7][2] = 0;
frame[7][3] = 0;
frame[7][4] = 0;
frame[7][5] = 0;
frame[7][6] = 0;
frame[7][7] = 0;
frame[7][8] = 0;
frame[7][9] = 0;
frame[7][10] = 0;
frame[7][11] = 0;
}

void menuOption1() {
frame[0][0] = 1;
frame[0][1] = 1;
frame[0][2] = 1;
frame[0][3] = 1;
frame[0][4] = 1;
frame[0][5] = 1;
frame[0][6] = 0;
frame[0][7] = 0;
frame[0][8] = 0;
frame[0][9] = 0;
frame[0][10] = 0;
frame[0][11] = 0;
frame[1][0] = 1;
frame[1][1] = 0;
frame[1][2] = 0;
frame[1][3] = 0;
frame[1][4] = 0;
frame[1][5] = 1;
frame[1][6] = 0;
frame[1][7] = 0;
frame[1][8] = 0;
frame[1][9] = 0;
frame[1][10] = 0;
frame[1][11] = 0;
frame[2][0] = 1;
frame[2][1] = 0;
frame[2][2] = 1;
frame[2][3] = 1;
frame[2][4] = 0;
frame[2][5] = 1;
frame[2][6] = 0;
frame[2][7] = 0;
frame[2][8] = 0;
frame[2][9] = 0;
frame[2][10] = 0;
frame[2][11] = 0;
frame[3][0] = 1;
frame[3][1] = 0;
frame[3][2] = 1;
frame[3][3] = 1;
frame[3][4] = 0;
frame[3][5] = 1;
frame[3][6] = 0;
frame[3][7] = 0;
frame[3][8] = 0;
frame[3][9] = 0;
frame[3][10] = 0;
frame[3][11] = 0;
frame[4][0] = 1;
frame[4][1] = 0;
frame[4][2] = 1;
frame[4][3] = 1;
frame[4][4] = 0;
frame[4][5] = 1;
frame[4][6] = 0;
frame[4][7] = 0;
frame[4][8] = 0;
frame[4][9] = 0;
frame[4][10] = 0;
frame[4][11] = 0;
frame[5][0] = 1;
frame[5][1] = 0;
frame[5][2] = 1;
frame[5][3] = 1;
frame[5][4] = 0;
frame[5][5] = 1;
frame[5][6] = 0;
frame[5][7] = 0;
frame[5][8] = 0;
frame[5][9] = 0;
frame[5][10] = 0;
frame[5][11] = 0;
frame[6][0] = 1;
frame[6][1] = 0;
frame[6][2] = 0;
frame[6][3] = 0;
frame[6][4] = 0;
frame[6][5] = 1;
frame[6][6] = 0;
frame[6][7] = 0;
frame[6][8] = 0;
frame[6][9] = 0;
frame[6][10] = 0;
frame[6][11] = 0;
frame[7][0] = 1;
frame[7][1] = 1;
frame[7][2] = 1;
frame[7][3] = 1;
frame[7][4] = 1;
frame[7][5] = 1;
frame[7][6] = 0;
frame[7][7] = 0;
frame[7][8] = 0;
frame[7][9] = 0;
frame[7][10] = 0;
frame[7][11] = 0;
}

void menuOption2() {
frame[0][0] = 0;
frame[0][1] = 0;
frame[0][2] = 0;
frame[0][3] = 0;
frame[0][4] = 0;
frame[0][5] = 0;
frame[0][6] = 1;
frame[0][7] = 1;
frame[0][8] = 1;
frame[0][9] = 1;
frame[0][10] = 1;
frame[0][11] = 1;
frame[1][0] = 0;
frame[1][1] = 0;
frame[1][2] = 0;
frame[1][3] = 0;
frame[1][4] = 0;
frame[1][5] = 0;
frame[1][6] = 1;
frame[1][7] = 0;
frame[1][8] = 0;
frame[1][9] = 0;
frame[1][10] = 0;
frame[1][11] = 1;
frame[2][0] = 0;
frame[2][1] = 0;
frame[2][2] = 0;
frame[2][3] = 0;
frame[2][4] = 0;
frame[2][5] = 0;
frame[2][6] = 1;
frame[2][7] = 0;
frame[2][8] = 1;
frame[2][9] = 1;
frame[2][10] = 0;
frame[2][11] = 1;
frame[3][0] = 0;
frame[3][1] = 0;
frame[3][2] = 0;
frame[3][3] = 0;
frame[3][4] = 0;
frame[3][5] = 0;
frame[3][6] = 1;
frame[3][7] = 0;
frame[3][8] = 1;
frame[3][9] = 1;
frame[3][10] = 0;
frame[3][11] = 1;
frame[4][0] = 0;
frame[4][1] = 0;
frame[4][2] = 0;
frame[4][3] = 0;
frame[4][4] = 0;
frame[4][5] = 0;
frame[4][6] = 1;
frame[4][7] = 0;
frame[4][8] = 1;
frame[4][9] = 1;
frame[4][10] = 0;
frame[4][11] = 1;
frame[5][0] = 0;
frame[5][1] = 0;
frame[5][2] = 0;
frame[5][3] = 0;
frame[5][4] = 0;
frame[5][5] = 0;
frame[5][6] = 1;
frame[5][7] = 0;
frame[5][8] = 1;
frame[5][9] = 1;
frame[5][10] = 0;
frame[5][11] = 1;
frame[6][0] = 0;
frame[6][1] = 0;
frame[6][2] = 0;
frame[6][3] = 0;
frame[6][4] = 0;
frame[6][5] = 0;
frame[6][6] = 1;
frame[6][7] = 0;
frame[6][8] = 0;
frame[6][9] = 0;
frame[6][10] = 0;
frame[6][11] = 1;
frame[7][0] = 0;
frame[7][1] = 0;
frame[7][2] = 0;
frame[7][3] = 0;
frame[7][4] = 0;
frame[7][5] = 0;
frame[7][6] = 1;
frame[7][7] = 1;
frame[7][8] = 1;
frame[7][9] = 1;
frame[7][10] = 1;
frame[7][11] = 1;
}

void wink() {
frame[1][3] = 0;
frame[1][4] = 0;
frame[2][3] = 1;
frame[2][4] = 1;
}

void wink2() {
frame[1][8] = 0;
frame[1][9] = 0;
frame[2][8] = 1;
frame[2][9] = 1;
}

void leftEye() {
frame[1][3] = 1;
frame[1][4] = 1;
frame[2][3] = 1;
frame[2][4] = 1;
}

void rightEye() {
frame[1][8] = 1;
frame[1][9] = 1;
frame[2][8] = 1;
frame[2][9] = 1;
}

void nose() {
frame[3][6] = 1;
frame[4][5] = 1;
frame[4][6] = 1;
frame[4][7] = 1;
}

void mouth() {
frame[5][3] = 1;
frame[5][9] = 1;
frame[6][3] = 1;
frame[6][4] = 1;
frame[6][5] = 1;
frame[6][6] = 1;
frame[6][7] = 1;
frame[6][8] = 1;
frame[6][9] = 1;
frame[7][6] = 0;
}

void mouth2() {
frame[5][3] = 0;
frame[5][9] = 0;
frame[6][3] = 1;
frame[6][4] = 1;
frame[6][5] = 1;
frame[6][6] = 1;
frame[6][7] = 1;
frame[6][8] = 1;
frame[6][9] = 1;
frame[7][6] = 0;
}

void acd_key1() {
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
FastLED.clear(true);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
String messagef = "   Humidite <|> Temperature";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(100);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(100);
menu2();
}


void acd_key3() {
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
FastLED.clear(true);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
String messagef = "   Index Uv <|> Pression";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(100);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(100);
menu3();
}

void acd_key4() {
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
FastLED.clear(true);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
String messagef = "   qualite air <|> open-meteo";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(100);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(100);
menu4();
}

void acd_key5() {
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
FastLED.clear(true);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
String messagef = "   Date-heure <|> Trivia";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(100);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(100);
menu6();
}

void sw2() {
if (digitalRead(12) == LOW) {
acd_key1();
}
if (digitalRead(11) == LOW) {
acd_key3();
}
if (digitalRead(10) == LOW) {
acd_key4();
}
if (digitalRead(9) == LOW) {
acd_key5();
}
if (digitalRead(SW) == LOW) {
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
FastLED.clear(true);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
String messagef = "   Snake <|> Flappy";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(100);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(100);
menu1();
}}

void timebot() {
u8g2.clear(); 
timeClient.update();
time_t epochTime2 = timeClient.getEpochTime();
unsigned long epochTime = timeClient.getEpochTime();
while (epochTime < 1707219755) {
epochTime = timeClient.getEpochTime();
delay(25);
}
struct tm *ptm = gmtime ((time_t *)&epochTime2);
int aYear = ptm->tm_year + 1900;
int amonth = ptm->tm_mon + 1;
int monthDay = ptm->tm_mday;
int aday = timeClient.getDay();
int ahoure = timeClient.getHours();
int aMinute = timeClient.getMinutes();
int aSeconds = ptm->tm_sec;
char timestamp[50];
if (ahoure < 10) {
if (aMinute < 10) {
snprintf(timestamp, 50, "%s %d %s %d - 0%d:0%d.", weekday[aday], monthDay, month[amonth], aYear, ahoure, aMinute);
}
else if (ahoure < 10 && aMinute >= 10) {
snprintf(timestamp, 50, "%s %d %s %d - 0%d:%d.", weekday[aday], monthDay, month[amonth], aYear, ahoure, aMinute);
} 
else {
snprintf(timestamp, 50, "%s %d %s %d - %d:%d.", weekday[aday], monthDay, month[amonth], aYear, ahoure, aMinute);
}}
else {
if (aMinute < 10) {
snprintf(timestamp, 50, "%s %d %s %d - %d:0%d.", weekday[aday], monthDay, month[amonth], aYear, ahoure, aMinute);
}
else {
snprintf(timestamp, 50, "%s %d %s %d - %d:%d.", weekday[aday], monthDay, month[amonth], aYear, ahoure, aMinute);
}}
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(40);
matrix.textFont(Font_5x7);
matrix.beginText(12, 1, 0xFFFFFF);
matrix.println(timestamp);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(200);
const char text123[] = "=";
matrix.textFont(Font_4x6);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(text123);
matrix.endText();
matrix.endDraw();
delay(200);
const char text124[] = "=>";
matrix.textFont(Font_4x6);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(text124);
matrix.endText();
matrix.endDraw();
delay(200);
const char text125[] = "=>>";
matrix.textFont(Font_4x6);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(text125);
matrix.endText();
matrix.endDraw();
u8g2.clearBuffer();
u8g2.firstPage();
do {
if (amonth == 1 || amonth == 3 || amonth == 5 || amonth == 7 || amonth == 8 || amonth == 10 || amonth == 12){
monthLength = 31;
}
else {monthLength = 30;}
if(amonth == 2){monthLength = 28;}
startDay = startDayOfWeek(aYear,amonth,1); 
switch (startDay){
case 0:
week1 = " 1   2   3   4   5   6   7";
break;
case 1:
week1 = "     1   2   3   4   5   6";
break;      
case 2:
week1 = "         1   2   3   4   5";
break;           
case 3:
week1 = "             1   2   3   4";
break;  
case 4:
week1 = "                 1   2   3";
break; 
case 5:
if(monthLength == 28 || monthLength == 30){week1 = "                     1   2";}      
if(monthLength == 31){week1 = "31                   1   2";}      
break; 
case 6:
if(monthLength == 28){week1 = "                         1";}
if(monthLength == 30){week1 = "30                       1";}      
if(monthLength == 31){week1 = "30 31                    1";}       
break;           
}
newWeekStart = (7-startDay)+1;
const char* newWeek1 = (const char*) week1.c_str();  
u8g2.setFont(u8g2_font_ncenB08_tr);           
u8g2.drawStr(9,50,newWeek1); 
week2 ="";
for (int f = newWeekStart; f < newWeekStart + 7; f++){
if(f<10){
week2 = week2 +  " " + String(f) + " ";
}  
else{week2 = week2 + String(f) + " ";}    
}
const char* newWeek2 = (const char*) week2.c_str();  
u8g2.setFont(u8g2_font_ncenB08_tr);           
u8g2.drawStr(9,65,newWeek2); 
newWeekStart = (14-startDay)+1; 
week3 ="";
for (int f = newWeekStart; f < newWeekStart + 7; f++){
if(f<10){
week3 = week3 +  " " + String(f) + " ";
}  
else{week3 = week3 + String(f) + " ";}    
}
const char* newWeek3 = (const char*) week3.c_str();  
u8g2.setFont(u8g2_font_ncenB08_tr);           
u8g2.drawStr(9,80,newWeek3);     
newWeekStart = (21-startDay)+1; 
week4 ="";
for (int f = newWeekStart; f < newWeekStart + 7; f++){
if(f<10){
week4 = week4 +  " " + String(f) + " ";
}  
else{week4 = week4 + String(f) + " ";}    
}
const char* newWeek4 = (const char*) week4.c_str();  
u8g2.setFont(u8g2_font_ncenB08_tr);           
u8g2.drawStr(9,95,newWeek4); 
week5="";
newWeekStart = (28-startDay)+1;   
if(newWeekStart > 28 && amonth == 2){
if (aYear==(aYear/4)*4){ 
week5 = "29";
}       }
else{ 
if(amonth == 2){ 
for (int f = newWeekStart; f < 29; f++){
week5 = week5 + String(f) + " ";  
}  
if (aYear==(aYear/4)*4){ // its a leap year
week5 = week5 + "29";
}        }
else{
for (int f = newWeekStart; f < 31; f++){
week5 = week5 + String(f) + " ";
}
if (monthLength == 31 && week5.length() <7){
week5 = week5 + "31"; 
}}}
const char* newWeek5 = (const char*) week5.c_str();  
u8g2.drawStr(9,110,newWeek5);
u8g2.drawFrame(3,3,125,16 );
u8g2.drawFrame(3,35,125,89 );
u8g2.setCursor(7, 15);
u8g2.setFont(u8g2_font_ncenB08_tr);           
u8g2.print(month[amonth]);
u8g2.setCursor(102, 15);
u8g2.setFont(u8g2_font_ncenB08_tr);           
u8g2.print(aYear);
u8g2.setCursor(8, 30);
u8g2.setFont(u8g2_font_squeezed_b7_tr);           
u8g2.print("Di");
u8g2.setCursor(22, 30);
u8g2.setFont(u8g2_font_squeezed_b7_tr);           
u8g2.print("Lu");
u8g2.setCursor(38, 30);
u8g2.setFont(u8g2_font_squeezed_b7_tr);           
u8g2.print("Ma");
u8g2.setCursor(56, 30);
u8g2.setFont(u8g2_font_squeezed_b7_tr);           
u8g2.print("Me");
u8g2.setCursor(72, 30);
u8g2.setFont(u8g2_font_squeezed_b7_tr);           
u8g2.print("Je");
u8g2.setCursor(85, 30);
u8g2.setFont(u8g2_font_squeezed_b7_tr);           
u8g2.print("Ve");
u8g2.setCursor(100, 30);
u8g2.setFont(u8g2_font_squeezed_b7_tr);           
u8g2.print("Sa");
}
while ( u8g2.nextPage() );
delay(5000);
u8g2.clear(); 
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(200);
leftEye();
rightEye();
nose();
mouth();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
wink();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
leftEye();
matrix.renderBitmap(frame, 8, 12);
delay(500);
}

void tempbot() {
int Temperature = dht.readTemperature();
char timestamp2[50];
snprintf(timestamp2, 50, "    Temperature: %d%s", Temperature, "C.");
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(40);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(timestamp2);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
leftEye();
rightEye();
nose();
mouth();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
wink();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
leftEye();
matrix.renderBitmap(frame, 8, 12);
delay(500);
return;
}

void Pressurebot() {
sensors_event_t event;
bmp.getEvent(&event);
if (event.pressure){
int pression = event.pressure;
char timestamp11[50];
snprintf(timestamp11, 50, "    Pression atmospherique: %d%s", pression, "hPa.");
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(40);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(timestamp11);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
leftEye();
rightEye();
nose();
mouth();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
wink();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
leftEye();
matrix.renderBitmap(frame, 8, 12);
delay(500);
}
else{
Serial.println("Sensor error");
}
return;
}

void humbot() {
int Humidity = dht.readHumidity();
char timestamp3[50];
snprintf(timestamp3, 50, "    Humidite: %d%s", Humidity, "%.");
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(40);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(timestamp3);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
leftEye();
rightEye();
nose();
mouth();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
wink();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
leftEye();
matrix.renderBitmap(frame, 8, 12);
delay(500);
return;
}

void uvbot() {
sensorValue2 = 0;
sum = 0;
for (int i = 0 ; i < 1024 ; i++ ){
sensorValue2 = analogRead(sensorPin);
sum = sensorValue2 + sum;
delay(1);
}
vout = sum >> 10;
vout = vout * 4980.0 / 4095;
Serial.print("The Photocurrent value:");
Serial.print(vout);
Serial.println("mV");
if (vout < 50){
uv = 0;
}
else if (vout < 227){
uv = 1;
}
else if (vout < 318){
uv = 2;
}
else if (vout < 408){
uv = 3;
}
else if (vout < 503){
uv = 4;
}
else if (vout < 606){
uv = 5;
}
else if (vout < 696){
uv = 6;
}
else if (vout < 795){
uv = 7;
}
else if (vout < 881){
uv = 8;
}
else if (vout < 976){
uv = 9;
}
else if (vout < 1079){
uv = 10;
}
else{
uv = 11;
}
delay(20);
Serial.print("UV Index = ");
Serial.println(uv);
char timestamp4[50];
snprintf(timestamp4, 50, "    Index valeur Uv: %d%s", uv, ".");
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(40);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(timestamp4);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
leftEye();
rightEye();
nose();
mouth();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
wink();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
leftEye();
matrix.renderBitmap(frame, 8, 12);
delay(500);
}

void menuMQ() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
int sensorValue = digitalRead(10);
delay(100);
joystick_pos3 = analogRead(A1) - 512;
if (joystick_pos3 < -450) {
const char text[] = "MQ9";
matrix.textFont(Font_4x6);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(text);
matrix.endText();
matrix.endDraw();
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
MQ9bot();
return;
}}
if (joystick_pos3 < -300 && joystick_pos3 >= -450) {
const char text[] = "MQ8";
matrix.textFont(Font_4x6);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(text);
matrix.endText();
matrix.endDraw();
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
MQ8bot();
return;
}}
if (joystick_pos3 < -150 && joystick_pos3 >= -300) {
const char text[] = "MQ7";
matrix.textFont(Font_4x6);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(text);
matrix.endText();
matrix.endDraw();
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
MQ7bot();
return;
}}
if (joystick_pos3 < -20 && joystick_pos3 >= -150) {
const char text[] = "MQ6";
matrix.textFont(Font_4x6);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(text);
matrix.endText();
matrix.endDraw();
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
MQ6bot();
return;
}}
if (joystick_pos3 >= -20 && joystick_pos3 <= 20) {
const char text[] = "MQ5";
matrix.textFont(Font_4x6);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(text);
matrix.endText();
matrix.endDraw();
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
MQ5bot();
return;
}}
if (joystick_pos3 >= 20 && joystick_pos3 <= 150) {
const char text[] = "MQ4";
matrix.textFont(Font_4x6);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(text);
matrix.endText();
matrix.endDraw();
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
MQ4bot();
return;
}}
if (joystick_pos3 > 150 && joystick_pos3 <= 300) {
const char text[] = "MQ3";
matrix.textFont(Font_4x6);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(text);
matrix.endText();
matrix.endDraw();
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
MQ3bot();
return;
}}
if (joystick_pos3 > 300 && joystick_pos3 <= 450) {
const char text[] = "MQ2";
matrix.textFont(Font_4x6);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(text);
matrix.endText();
matrix.endDraw();
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
MQ2bot();
return;
}}
if (joystick_pos3 > 450) {
const char text[] = "MQ135";
matrix.textFont(Font_4x6);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(text);
matrix.endText();
matrix.endDraw();
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
MQ135bot();
return;
}}
menuMQ();
}

void MQ135bot() {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
MQ.RSRoMQAir(3.6);
MQ.setRL(20);
MQ.dangerousPer(42.5);
int CO = MQ.MQ135DataCO();
MQ.dangerousPer(25.55);
int Alcohol = MQ.MQ135DataAlcohol();
MQ.dangerousPer(27.77);
int CO2 = MQ.MQ135DataCO2();
MQ.dangerousPer(21.944);
int Toluen = MQ.MQ135DataToluen();
MQ.dangerousPer(29.166);
int NH4 = MQ.MQ135DataNH4();
MQ.dangerousPer(20.55);
int Aceton = MQ.MQ135DataAceton();
int Air = MQ.MQ135DataAir();
Serial.println("CO:");
Serial.println(CO);
Serial.println("CO2:");
Serial.println(CO2);
Serial.println("Alcool:");
Serial.println(Alcohol);
Serial.println("Methylbenzene:");
Serial.println(Toluen);
Serial.println("Ammonium:");
Serial.println(NH4);
Serial.println("Aceton:");
Serial.println(Aceton);
Serial.println("air:");
Serial.println(Air);
char timestamp88[150];
snprintf(timestamp88, 150, "    Pollution generale: %dppm - CO: %dppm - CO2: %dppm - Alcool: %dppm - Methylbenzene: %dppm - Ammonium: %dppm - Aceton: %dppm.", Air, CO, CO2,Alcohol, Toluen, NH4, Aceton);
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(40);
matrix.textFont(Font_5x7);
matrix.beginText(12, 1, 0xFFFFFF);
matrix.println(timestamp88);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
leftEye();
rightEye();
nose();
mouth();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
wink();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
leftEye();
matrix.renderBitmap(frame, 8, 12);
delay(500);
}

void MQ2bot() {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
MQ.RSRoMQAir(9.8);
MQ.setRL(20);
MQ.dangerousPer(10.2); 
int H2 = MQ.MQ2DataH2();
MQ.dangerousPer(7.96);
int LPG = MQ.MQ2DataLPG();
MQ.dangerousPer(31.63);
int CO = MQ.MQ2DataCO();
MQ.dangerousPer(16.33);
int Alcohol = MQ.MQ2DataAlcohol();
MQ.dangerousPer(8.38);
int Propane = MQ.MQ2DataPropane();
MQ.dangerousPer(17.86);
int CH4 = MQ.MQ2DataCH4(); 
MQ.dangerousPer(18.98);
int Smoke = MQ.MQ2Datasmoke();
int Air = MQ.MQ2DataAir();
Serial.println("Dihydrogene:");
Serial.println(H2);
Serial.println("LPG:");
Serial.println(LPG);
Serial.println("CO:");
Serial.println(CO);
Serial.println("Alcool:");
Serial.println(Alcohol);
Serial.println("Propane:");
Serial.println(Propane);
Serial.println("Ammonium:");
Serial.println(CH4);
Serial.println("Fumee:");
Serial.println(Smoke);
Serial.println("air:");
Serial.println(Air);
char timestamp89[150];
snprintf(timestamp89, 150, "    Dihydrogene: %dppm - LPG: %dppm - CO: %dppm - Alcool: %dppm - Propane: %dppm - Ammonium: %dppm - Fumee: %dppm.", H2, LPG, CO, Alcohol, Propane, CH4, Smoke);
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(40);
matrix.textFont(Font_5x7);
matrix.beginText(12, 1, 0xFFFFFF);
matrix.println(timestamp89);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
leftEye();
rightEye();
nose();
mouth();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
wink();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
leftEye();
matrix.renderBitmap(frame, 8, 12);
delay(500);
}

void MQ3bot() {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
MQ.dangerousPer(48.97);
int LPG = MQ.MQ3DataLPG();
MQ.dangerousPer(74.69);
int CH4 = MQ.MQ3DataCH4();
MQ.dangerousPer(57);
int CO = MQ.MQ3DataCO();
MQ.dangerousPer(0.67);
int Alcohol = MQ.MQ3DataAlcohol();
MQ.dangerousPer(2.92);
int Benzene = MQ.MQ3DataBenzene();
MQ.dangerousPer(38);
int Hexane = MQ.MQ3DataHexane();
int Air = MQ.MQ3DataAir();
Serial.println("LPG:");
Serial.println(LPG);
Serial.println("Ammonium:");
Serial.println(CH4);
Serial.println("CO:");
Serial.println(CO);
Serial.println("Alcool:");
Serial.println(Alcohol);
Serial.println("Benzene:");
Serial.println(Benzene);
Serial.println("Hexane:");
Serial.println(Hexane);
Serial.println("Air:");
Serial.println(Air);
char timestamp82[150];
snprintf(timestamp82, 150, "    LPG: %dppm - Ammonium: %dppm - CO: %dppm - Alcool: %dppm - Benzene: %dppm - Hexane: %dppm.", LPG, CH4, CO, Alcohol, Benzene, Hexane);
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(40);
matrix.textFont(Font_5x7);
matrix.beginText(12, 1, 0xFFFFFF);
matrix.println(timestamp82);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
leftEye();
rightEye();
nose();
mouth();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
wink();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
leftEye();
matrix.renderBitmap(frame, 8, 12);
delay(500);
}

void MQ4bot() {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
MQ.RSRoMQAir(4.4);
MQ.setRL(20);
MQ.dangerousPer(64.43);
int H2 = MQ.MQ4DataH2();
MQ.dangerousPer(34.32);
int LPG = MQ.MQ4DataLPG();
MQ.dangerousPer(22.73);
int CH4 = MQ.MQ4DataCH4();
MQ.dangerousPer(86.14);
int CO = MQ.MQ4DataCO();
MQ.dangerousPer(82.05);
int Alcohol = MQ.MQ4DataAlcohol();
MQ.dangerousPer(80.23);
int Smoke = MQ.MQ4DataSmoke();
int Air = MQ.MQ4DataAir(); 
Serial.println("Dihydrogene:");
Serial.println(H2);
Serial.println("LPG:");
Serial.println(LPG);
Serial.println("Ammonium:");
Serial.println(CH4);
Serial.println("CO:");
Serial.println(CO);
Serial.println("Alcool:");
Serial.println(Alcohol);
Serial.println("Fumee:");
Serial.println(Smoke);
Serial.println("Air:");
Serial.println(Air);
char timestamp83[150];
snprintf(timestamp83, 150, "    Dihydrogene: %dppm - LPG: %dppm - Ammonium: %dppm - CO: %dppm - Alcool: %dppm - Fumee: %dppm.", H2, LPG, CH4, CO, Alcohol, Smoke);
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(40);
matrix.textFont(Font_5x7);
matrix.beginText(12, 1, 0xFFFFFF);
matrix.println(timestamp83);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
leftEye();
rightEye();
nose();
mouth();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
wink();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
leftEye();
matrix.renderBitmap(frame, 8, 12);
delay(500);
}

void MQ5bot() {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
MQ.RSRoMQAir(6.5);
MQ.setRL(20);
MQ.dangerousPer(15.12);
int H2 = MQ.MQ5DataH2();
MQ.dangerousPer(5.54);
int LPG = MQ.MQ5DataLPG();
MQ.dangerousPer(7.92);
int CH4 = MQ.MQ5DataCH4();
MQ.dangerousPer(44.15);
int CO = MQ.MQ5DataCO();
MQ.dangerousPer(39.38);
int Alcohol = MQ.MQ5DataAlcohol();
int Air = MQ.MQ5DataAir();
Serial.println("Dihydrogene:");
Serial.println(H2);
Serial.println("LPG:");
Serial.println(LPG);
Serial.println("Ammonium:");
Serial.println(CH4);
Serial.println("CO:");
Serial.println(CO);
Serial.println("Alcool:");
Serial.println(Alcohol);
Serial.println("Air:");
Serial.println(Air);
char timestamp84[150];
snprintf(timestamp84, 150, "    Dihydrogene: %dppm - LPG: %dppm - Ammonium: %dppm - CO: %dppm - Alcool: %dppm.", H2, LPG, CH4, CO, Alcohol);
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(40);
matrix.textFont(Font_5x7);
matrix.beginText(12, 1, 0xFFFFFF);
matrix.println(timestamp84);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
leftEye();
rightEye();
nose();
mouth();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
wink();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
leftEye();
matrix.renderBitmap(frame, 8, 12);
delay(500);
}

void MQ6bot() {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
MQ.RSRoMQAir(10);
MQ.setRL(20);
MQ.dangerousPer(33.7);
int H2 = MQ.MQ6DataH2();
MQ.dangerousPer(10);
int LPG = MQ.MQ6DataLPG();
MQ.dangerousPer(13.5);
int CH4 = MQ.MQ6DataCH4();
MQ.dangerousPer(78);
int CO = MQ.MQ6DataCO();
MQ.dangerousPer(61.2);
int Alcohol = MQ.MQ6DataAlcohol();
int Air = MQ.MQ6DataAir();
Serial.println("Dihydrogene:");
Serial.println(H2);
Serial.println("LPG:");
Serial.println(LPG);
Serial.println("Ammonium:");
Serial.println(CH4);
Serial.println("CO:");
Serial.println(CO);
Serial.println("Alcool:");
Serial.println(Alcohol);
Serial.println("Air:");
Serial.println(Air);
char timestamp87[150];
snprintf(timestamp87, 150, "    Dihydrogene: %dppm - LPG: %dppm - Ammonium: %dppm - CO: %dppm - Alcool: %dppm.", H2, LPG, CH4, CO, Alcohol);
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(40);
matrix.textFont(Font_5x7);
matrix.beginText(12, 1, 0xFFFFFF);
matrix.println(timestamp87);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
leftEye();
rightEye();
nose();
mouth();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
wink();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
leftEye();
matrix.renderBitmap(frame, 8, 12);
delay(500);
}

void MQ7bot() {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
MQ.RSRoMQAir(26);
MQ.setRL(10);
MQ.dangerousPer(3.08);
int H2 = MQ.MQ7DataH2();
MQ.dangerousPer(30.77);
int LPG = MQ.MQ7DataLPG();
MQ.dangerousPer(49.18);
int CH4 = MQ.MQ7DataCH4();
MQ.dangerousPer(3.85);
int CO = MQ.MQ7DataCO();
MQ.dangerousPer(57.69);
int Alcohol = MQ.MQ7DataAlcohol();
int Air = MQ.MQ7DataAir();
Serial.println("Dihydrogene:");
Serial.println(H2);
Serial.println("LPG:");
Serial.println(LPG);
Serial.println("Ammonium:");
Serial.println(CH4);
Serial.println("CO:");
Serial.println(CO);
Serial.println("Alcool:");
Serial.println(Alcohol);
Serial.println("Air:");
Serial.println(Air);
char timestamp87[150];
snprintf(timestamp87, 150, "    Dihydrogene: %dppm - LPG: %dppm - Ammonium: %dppm - CO: %dppm - Alcool: %dppm.", H2, LPG, CH4, CO, Alcohol);
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(40);
matrix.textFont(Font_5x7);
matrix.beginText(12, 1, 0xFFFFFF);
matrix.println(timestamp87);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
leftEye();
rightEye();
nose();
mouth();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
wink();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
leftEye();
matrix.renderBitmap(frame, 8, 12);
delay(500);
}

void MQ8bot() {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
MQ.RSRoMQAir(70);
MQ.setRL(10);
MQ.dangerousPer(1.43);
int H2 = MQ.MQ8DataH2();
MQ.dangerousPer(27.53);
int LPG = MQ.MQ8DataLPG();
MQ.dangerousPer(63.47);
int CH4 = MQ.MQ8DataCH4();
MQ.dangerousPer(80.57);
int CO = MQ.MQ8DataCO();
MQ.dangerousPer(14.81);
int Alcohol = MQ.MQ8DataAlcohol();
int Air = MQ.MQ8DataAir();
Serial.println("Dihydrogene:");
Serial.println(H2);
Serial.println("LPG:");
Serial.println(LPG);
Serial.println("Ammonium:");
Serial.println(CH4);
Serial.println("CO:");
Serial.println(CO);
Serial.println("Alcool:");
Serial.println(Alcohol);
Serial.println("Air:");
Serial.println(Air);
char timestamp87[150];
snprintf(timestamp87, 150, "    Dihydrogene: %dppm - LPG: %dppm - Ammonium: %dppm - CO: %dppm - Alcool: %dppm.", H2, LPG, CH4, CO, Alcohol);
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(40);
matrix.textFont(Font_5x7);
matrix.beginText(12, 1, 0xFFFFFF);
matrix.println(timestamp87);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
leftEye();
rightEye();
nose();
mouth();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
wink();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
leftEye();
matrix.renderBitmap(frame, 8, 12);
delay(500);
}

void MQ9bot() {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
MQ.RSRoMQAir(9.7);
MQ.setRL(20);
MQ.dangerousPer(10.31);
int LPG = MQ.MQ9DataLPG();
MQ.dangerousPer(18.04);
int CH4 = MQ.MQ9DataCH4();
MQ.dangerousPer(8);
int CO = MQ.MQ9DataCO();
int Air = MQ.MQ9DataAir();
Serial.println("LPG:");
Serial.println(LPG);
Serial.println("Ammonium:");
Serial.println(CH4);
Serial.println("CO:");
Serial.println(CO);
Serial.println("Air:");
Serial.println(Air);
char timestamp87[150];
snprintf(timestamp87, 150, "    LPG: %dppm - Ammonium: %dppm - CO: %dppm.", LPG, CH4, CO);
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(40);
matrix.textFont(Font_5x7);
matrix.beginText(12, 1, 0xFFFFFF);
matrix.println(timestamp87);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
leftEye();
rightEye();
nose();
mouth();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
wink();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
leftEye();
matrix.renderBitmap(frame, 8, 12);
delay(500);
}

void face() {
int ahoure = timeClient.getHours();
if (ahoure >= 0 && ahoure < 8) {
wink();
wink2();
nose();
mouth2();
matrix.renderBitmap(frame, 8, 12);
}
else {
leftEye();
rightEye();
nose();
mouth();
matrix.renderBitmap(frame, 8, 12);
}}

void setupwelcome() {
matrix.loadFrame(heart);
delay(1000);
matrix.loadFrame(LEDMATRIX_LIKE);
delay(1000);
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(40);
const char text0[] = "   Super Botje.";
matrix.textFont(Font_4x6);
matrix.beginText(12, 1, 0xFFFFFF);
matrix.println(text0);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
leftEye();
rightEye();
nose();
mouth();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
wink();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
leftEye();
matrix.renderBitmap(frame, 8, 12);
delay(500);
}

void song() {
for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
divider = melody[thisNote + 1];
if (divider > 0) {
noteDuration = (wholenote) / divider;
} 
else if (divider < 0) {
noteDuration = (wholenote) / abs(divider);
noteDuration *= 1.5;
}
tone(buzzer, melody[thisNote], noteDuration * 0.9);
delay(noteDuration);
noTone(buzzer);
}}

void menu1() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
delay(100);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
joystick_pos = analogRead(A0) - 512;
if (joystick_pos > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (digitalRead(SW) == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
flappy();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (digitalRead(SW) == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
snakeStart();
return;
}}
menu1();
}

void menu2() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
int sensorValue = digitalRead(12);
delay(100);
joystick_pos2 = analogRead(A0) - 512;
if (joystick_pos2 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tempbot();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
humbot();
return;
}}
menu2();
}

void menu3() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
int sensorValue = digitalRead(11);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
Pressurebot();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
uvbot();
return;
}}
menu3();
}

void menu4() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
int sensorValue = digitalRead(10);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
openmeteo();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
menuMQ();
return;
}}
menu4();
}

void menu6() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaStart();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
timebot();
return;
}}
menu6();
}

void flappysong() {
tone(buzzer, 1047);
flappy1();
delay(200);
noTone(buzzer);
tone(buzzer, 1047);
delay(200);
noTone(buzzer);
tone(buzzer, 1319);
delay(200);
noTone(buzzer);
tone(buzzer, 1568);
delay(200);
noTone(buzzer);
delay(200);
tone(buzzer, 1568);
delay(200);
noTone(buzzer);
delay(200);
tone(buzzer, 1568);
delay(200);
noTone(buzzer);
tone(buzzer, 1760);
delay(200);
noTone(buzzer);
tone(buzzer, 1568);
delay(200);
noTone(buzzer);
tone(buzzer, 1319);
delay(200);
noTone(buzzer);
tone(buzzer, 1047);
delay(200);
noTone(buzzer);
delay(200);
tone(buzzer, 1047);
delay(200);
noTone(buzzer);
delay(200);
tone(buzzer, 784);
delay(200);
noTone(buzzer);
tone(buzzer, 880);
delay(200);
noTone(buzzer);
tone(buzzer, 880);
delay(200);
noTone(buzzer);
tone(buzzer, 1175);
delay(200);
noTone(buzzer);
tone(buzzer, 1047);
delay(200);
noTone(buzzer);
delay(200);
tone(buzzer, 1047);
delay(200);
noTone(buzzer);
delay(200);
tone(buzzer, 1175);
delay(200);
noTone(buzzer);
tone(buzzer, 1319);
delay(200);
noTone(buzzer);
tone(buzzer, 1175);
delay(200);
noTone(buzzer);
tone(buzzer, 1319);
delay(200);
noTone(buzzer);
tone(buzzer, 1175);
delay(200);
noTone(buzzer);
}

void flappy() {
u8g2.clear();
digitalWrite(RPin, HIGH);
flappysong();
line_pos = 11;
line_height = random(1, 6);
String messagef = "   3...2...1";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(100);
digitalWrite(RPin, RState);
delay(250);
tone(buzzer, 1047);
delay(200);
noTone(buzzer);
flappygame();
}

void flappyOver() {
digitalWrite(green_led, LOW);
digitalWrite(red_led, HIGH);
u8g2.clear(); 
delay(200);
over2();
delay(500);
String messagef2 = "   -Game Over-";
tone(buzzer, NOTE_D4);
delay(100);
tone(buzzer, NOTE_B4);
delay(200);
noTone(buzzer);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(100);
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef2);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
delay(100);
digitalWrite(red_led, LOW);
digitalWrite(green_led, HIGH);
delay(500);
u8g2.clear(); 
delay(200);
leftEye();
rightEye();
nose();
mouth();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
wink();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
leftEye();
matrix.renderBitmap(frame, 8, 12);
delay(500);
}

void flappygame() {
sw_state = !digitalRead(SW);
if (line_pos <= 0) {
line_pos = 11;
line_height = random(1, 6);
} 
else {
line_pos--;
}
frame[0][line_pos] = 1;
draw_line(line_height, line_pos);
if (sw_state) {
if (player_pos > 0)
player_pos--;
} else {
if (player_pos < 7)
player_pos++;
}
if (line_pos == 2 && ((7 - line_height) < player_pos || player_pos == 0)) {
while (HIGH) {
flappyOver();
delay(150);
return;
}}
frame[player_pos][2] = 1;
matrix.renderBitmap(frame, 8, 12);
memset(frame, 0, sizeof(frame));
delay(150);
flappygame();
}

void snakesong() {
snake1();
tone(buzzer, 659);
delay(182);
noTone(buzzer);
tone(buzzer, 740);
delay(91);
noTone(buzzer);
tone(buzzer, 880);
delay(182);
noTone(buzzer);
tone(buzzer, 1109);
delay(273);
noTone(buzzer);
tone(buzzer, 880);
delay(91);
noTone(buzzer);
tone(buzzer, 740);
delay(273);
noTone(buzzer);
tone(buzzer, 659);
delay(182);
noTone(buzzer);
tone(buzzer, 740);
delay(91);
noTone(buzzer);
tone(buzzer, 880);
delay(182);
noTone(buzzer);
tone(buzzer, 1047);
delay(273);
noTone(buzzer);
tone(buzzer, 880);
delay(91);
noTone(buzzer);
tone(buzzer, 740);
delay(273);
noTone(buzzer);
tone(buzzer, 659);
delay(182);
noTone(buzzer);
tone(buzzer, 740);
delay(91);
noTone(buzzer);
tone(buzzer, 880);
delay(182);
noTone(buzzer);
tone(buzzer, 1109);
delay(273);
noTone(buzzer);
tone(buzzer, 880);
delay(91);
noTone(buzzer);
tone(buzzer, 1109);
delay(182);
noTone(buzzer);
tone(buzzer, 1175);
delay(91);
noTone(buzzer);
tone(buzzer, 1319);
delay(182);
noTone(buzzer);
tone(buzzer, 1175);
delay(91);
noTone(buzzer);
tone(buzzer, 1047);
delay(182);
noTone(buzzer);
tone(buzzer, 880);
delay(91);
noTone(buzzer);
tone(buzzer, 1047);
delay(182);
noTone(buzzer);
tone(buzzer, 880);
delay(91);
noTone(buzzer);
tone(buzzer, 659);
delay(455);
noTone(buzzer);
tone(buzzer, 554);
delay(273);
noTone(buzzer);
tone(buzzer, 440);
delay(364);
noTone(buzzer);
tone(buzzer, 659);
delay(455);
noTone(buzzer);
tone(buzzer, 523);
delay(273);
noTone(buzzer);
tone(buzzer, 440);
delay(364);
noTone(buzzer);
tone(buzzer, 659);
delay(455);
noTone(buzzer);
tone(buzzer, 554);
delay(273);
noTone(buzzer);
tone(buzzer, 440);
delay(273);
noTone(buzzer);
tone(buzzer, 659);
delay(91);
noTone(buzzer);
tone(buzzer, 523);
delay(182);
noTone(buzzer);
tone(buzzer, 440);
delay(91);
noTone(buzzer);
tone(buzzer, 208);
delay(273);
noTone(buzzer);
tone(buzzer, 415);
delay(182);
noTone(buzzer);
tone(buzzer, 440);
delay(364);
noTone(buzzer);
}

void moveSnake() {
for (int i = snakeLength - 1; i > 0; i--) {
snake[i] = snake[i - 1];
}
switch (direction) {
case 0:
snake[0].y = (snake[0].y - 1 + 8) % 8;
break;
case 1:
snake[0].x = (snake[0].x + 1) % 12; 
break;
case 2:
snake[0].y = (snake[0].y + 1) % 8;
break;
case 3:
snake[0].x = (snake[0].x - 1 + 12) % 12;
break;
}}

void generateFood() {
Point possibleLocations[8 * 12];
int idx = 0;
for (int y = 0; y < 8; y++) {
for (int x = 0; x < 12; x++) {
bool overlap = false;
for (int i = 0; i < snakeLength; i++) {
if (snake[i].x == x && snake[i].y == y) {
overlap = true;
break;
}}
if (!overlap) {
possibleLocations[idx++] = { x, y };
}}}
int choice = random(0, idx);
food = possibleLocations[choice];
}

void drawFrame() {
for (int y = 0; y < 8; y++) {
for (int x = 0; x < 12; x++) {
frame2[y][x] = 0;
}}
for (int i = 0; i < snakeLength; i++) {
frame2[snake[i].y][snake[i].x] = 1;
}
frame2[food.y][food.x] = 1;
int idx = 0;
for (int y = 0; y < 8; y++) {
for (int x = 0; x < 12; x++) {
flatFrame[idx++] = frame2[y][x];
}}
matrix.loadPixels(flatFrame, 8 * 12);
matrix.renderFrame(0);
}

void snakeStart() {
u8g2.clear();
digitalWrite(RPin, HIGH);
snakesong();
String messagef = "   3...2...1";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(100);
digitalWrite(RPin, RState);
delay(250);
tone(buzzer, 1047);
delay(200);
noTone(buzzer);
snakeLength = 3;
snake[0] = { 6, 4 };
snake[1] = { 6, 5 };
snake[2] = { 6, 6 };
direction = 0;
generateFood();
snakeGame();
}

void snakeOver() {
digitalWrite(green_led, LOW);
digitalWrite(red_led, HIGH);
u8g2.clear(); 
delay(200);
over2();
delay(500);
String messagef2 = "   -Game Over-";
tone(buzzer, NOTE_D4);
delay(100);
tone(buzzer, NOTE_B4);
delay(200);
noTone(buzzer);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(100);
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef2);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
delay(100);
digitalWrite(red_led, LOW);
digitalWrite(green_led, HIGH);
delay(500);
u8g2.clear(); 
delay(200);
leftEye();
rightEye();
nose();
mouth();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
wink();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
leftEye();
matrix.renderBitmap(frame, 8, 12);
delay(500);
}

void snakeGame() {
int x = analogRead(A0);
int y = analogRead(A1);
if (x > 600 && direction != 3) direction = 1;
else if (x < 400 && direction != 1) direction = 3;
else if (y > 600 && direction != 0) direction = 2;
else if (y < 400 && direction != 2) direction = 0;
moveSnake();
if (snake[0].x == food.x && snake[0].y == food.y) {
snake[snakeLength] = snake[snakeLength - 1]; 
snakeLength++;
generateFood();
}
for (int i = 1; i < snakeLength; i++) {
if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
snakeOver();
return;
}}
drawFrame();
delay(200);
snakeGame();
}

void shuffleArray(int* array, int size) {
for (int i = size - 1; i > 0; i--) {
int j = random(0, i + 1);
if (i != j) {
int temp = array[i];
array[i] = array[j];
array[j] = temp;
}}}

void triviaStart() {
u8g2.clear();
static int questionIndices[50];
static int currentQuestionIndex = 0;
if (currentQuestionIndex == 0) {
for (int i = 0; i < 50; i++) {
questionIndices[i] = i;
}
shuffleArray(questionIndices, 50);
} 
delay(100);
line_pos = 11;
line_height = random(1, 6);
char* questions[] = {
"Qui est numero 1 de tous les temps sur la liste des championnes de tennis feminin du Grand Chelem ?", 
"De combien de touches un piano classique est-il dote ?", 
"Comment appelle-t-on une bande de corbeaux rassembles a terre ?", 
"Quel est le muscle humain le plus fort ?", 
"Quel est le plus petit oiseau du monde ?", 
"Quel a ete le premier dessin anime en couleur de Disney ?", 
"En quelle annee le Parrain a-t-il ete publie pour la premiere fois ?", 
"En quelle annee les Beatles se sont-ils rendus aux Etats-Unis pour la premiere fois ?", 
"Quelle est la taille de la grille sur un jeu de Scrabble ?", 
"Combien y a-t-il de couleurs dans un arc-en-ciel ?", 
"Quel champignon existe pas ?", 
"Le bambou appartient a la famille des ?", 
"Il existe de nombreuses varietes orchidees, mais elles possedent toutes les memes caracteristiques ?", 
"Dans hemisphere Nord, le jour le plus long est le ?", 
"De quel cote du bateau se trouve tribord ?", 
"Avec quelle lettre les Romains representaient-ils le chiffre 500 ?", 
"Alhambra est un palais situe a Grenade, en Espagne. Ce nomvient du arabe et signifie ?", 
"Le parc national des Everglades en Floride est celebre pour ?", 
"Ou vient le nom Barbie ?", 
"Quand la television a-t-elle ete inventee ?", 
"Quel est le plus long fleuve du monde ?", 
"Quel est le plus grand ocean de la Terre ?", 
"Quelle est la plus grande ile du monde en termes de superficie ?", 
"Quelle est la capitale la plus septentrionale du monde ?", 
"Quel est le pays le plus densement peuple de Afrique ?", 
"Ou se trouve le plus ancien pont en pierre du monde encore en usage ?", 
"Quel est le point culminant de ile de Java en Indonesie ?", 
"Quelle est la devise officielle de Union europeenne en latin ?", 
"Qui a invente le World Wide Web en 1989 ?", 
"Quel pays a remporte la toute premiere Coupe du Monde de football en 1930 ?", 
"Quelle est la langue officielle du Mexique ?", 
"Qui a peint -Les Nympheas- ?", 
"Quelle est la plus grande ville de Afrique ?", 
"Quel evenement a declenche la Premiere Guerre mondiale ?", 
"Quelle est la piece de Shakespeare la plus longue ?", 
"Quel est le plus haut gratte-ciel du monde ?", 
"Quelle est la capitale du Canada ?", 
"Qui a ecrit -Moby Dick- ?", 
"Quel est le plus grand lac Amerique du Nord ?", 
"Quel est le plus grand archipel du monde ?", 
"Qui a ecrit -Les Fleurs du mal- ?", 
"Qui a decouvert la penicilline ?", 
"Ou se trouve la statue du Christ Redempteur ?", 
"Quelle est la plus ancienne civilisation du monde ?", 
"Qui a joue le role de James Bond dans le film -Casino Royale- en 2006 ?", 
"Quelle est la devise nationale des Etats-Unis ?", 
"Dans quelle ville se trouve la maison des Simpson ?", 
"Dans les annees 60, qui invitait en chantant -Viens à la maison, y a le printemps qui chante- ?", 
"Quel style de nage n-est pas autorise aux Jeux olympiques ?", 
"Quelle equipe a remporte le premier match NBA en 1946 ?"};
int index = questionIndices[currentQuestionIndex];
char timestamp17[150];
snprintf(timestamp17, 150, "    %s", questions[index]);
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(timestamp17);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
delay(250);
currentQuestionIndex = (currentQuestionIndex + 1) % 50;
String selectedQuestion = questions[index];
if (selectedQuestion == "Qui est numero 1 de tous les temps sur la liste des championnes de tennis feminin du Grand Chelem ?") {
vraag1();
} 
else if (selectedQuestion == "De combien de touches un piano classique est-il dote ?") {
vraag2();
} 
else if (selectedQuestion == "Comment appelle-t-on une bande de corbeaux rassembles a terre ?") {
vraag3();
}
else if (selectedQuestion == "Quel est le muscle humain le plus fort ?") {
vraag4();
} 
else if (selectedQuestion == "Quel est le plus petit oiseau du monde ?") {
vraag5();
} 
else if (selectedQuestion == "Quel a ete le premier dessin anime en couleur de Disney ?") {
vraag6();
} 
else if (selectedQuestion == "En quelle annee le Parrain a-t-il ete publie pour la premiere fois ?") {
vraag7();
} 
else if (selectedQuestion == "En quelle annee les Beatles se sont-ils rendus aux Etats-Unis pour la premiere fois ?") {
vraag8();
} 
else if (selectedQuestion == "Quelle est la taille de la grille sur un jeu de Scrabble ?") {
vraag9();
} 
else if (selectedQuestion == "Combien y a-t-il de couleurs dans un arc-en-ciel ?") {
vraag10();
}
else if (selectedQuestion == "Quel champignon existe pas ?") {
vraag11();
}
else if (selectedQuestion == "Le bambou appartient a la famille des ?") {
vraag12();
}
else if (selectedQuestion == "Il existe de nombreuses varietes orchidees, mais elles possedent toutes les memes caracteristiques ?") {
vraag13();
}
else if (selectedQuestion == "Dans hemisphere Nord, le jour le plus long est le ?") {
vraag14();
}
else if (selectedQuestion == "De quel cote du bateau se trouve tribord ?") {
vraag15();
}
else if (selectedQuestion == "Avec quelle lettre les Romains representaient-ils le chiffre 500 ?") {
vraag16();
}
else if (selectedQuestion == "Alhambra est un palais situe a Grenade, en Espagne. Ce nomvient du arabe et signifie ?") {
vraag17();
}
else if (selectedQuestion == "Le parc national des Everglades en Floride est celebre pour ?") {
vraag18();
}
else if (selectedQuestion == "Ou vient le nom Barbie ?") {
vraag19();
}
else if (selectedQuestion == "Quand la television a-t-elle ete inventee ?") {
vraag20();
}
else if (selectedQuestion == "Quel est le plus long fleuve du monde ?") {
vraag21();
}
else if (selectedQuestion == "Quel est le plus grand ocean de la Terre ?") {
vraag22();
}
else if (selectedQuestion == "Quelle est la plus grande ile du monde en termes de superficie ?") {
vraag23();
}
else if (selectedQuestion == "Quelle est la capitale la plus septentrionale du monde ?") {
vraag24();
}
else if (selectedQuestion == "Quel est le pays le plus densement peuple de Afrique ?") {
vraag25();
}
else if (selectedQuestion == "Ou se trouve le plus ancien pont en pierre du monde encore en usage ?") {
vraag26();
}
else if (selectedQuestion == "Quel est le point culminant de ile de Java en Indonesie ?") {
vraag27();
}
else if (selectedQuestion == "Quelle est la devise officielle de Union europeenne en latin ?") {
vraag28();
}
else if (selectedQuestion == "Qui a invente le World Wide Web en 1989 ?") {
vraag29();
}
else if (selectedQuestion == "Quel pays a remporte la toute premiere Coupe du Monde de football en 1930 ?") {
vraag30();
}
else if (selectedQuestion == "Quelle est la langue officielle du Mexique ?") {
vraag31();
}
else if (selectedQuestion == "Qui a peint -Les Nympheas- ?") {
vraag32();
}
else if (selectedQuestion == "Quelle est la plus grande ville de Afrique ?") {
vraag33();
}
else if (selectedQuestion == "Quel evenement a declenche la Premiere Guerre mondiale ?") {
vraag34();
}
else if (selectedQuestion == "Quelle est la piece de Shakespeare la plus longue ?") {
vraag35();
}
else if (selectedQuestion == "Quel est le plus haut gratte-ciel du monde ?") {
vraag36();
}
else if (selectedQuestion == "Quelle est la capitale du Canada ?") {
vraag37();
}
else if (selectedQuestion == "Qui a ecrit -Moby Dick- ?") {
vraag38();
}
else if (selectedQuestion == "Quel est le plus grand lac Amerique du Nord ?") {
vraag39();
}
else if (selectedQuestion == "Quel est le plus grand archipel du monde ?") {
vraag40();
}
else if (selectedQuestion == "Qui a ecrit -Les Fleurs du mal- ?") {
vraag41();
}
else if (selectedQuestion == "Qui a decouvert la penicilline ?") {
vraag42();
}
else if (selectedQuestion == "Ou se trouve la statue du Christ Redempteur ?") {
vraag43();
}
else if (selectedQuestion == "Quelle est la plus ancienne civilisation du monde ?") {
vraag44();
}
else if (selectedQuestion == "Qui a joué le role de James Bond dans le film -Casino Royale- en 2006 ?") {
vraag45();
}
else if (selectedQuestion == "Quelle est la devise nationale des Etats-Unis ?") {
vraag46();
}
else if (selectedQuestion == "Dans quelle ville se trouve la maison des Simpson ?") {
vraag47();
}
else if (selectedQuestion == "Dans les annees 60, qui invitait en chantant -Viens à la maison, y a le printemps qui chante- ?") {
vraag48();
}
else if (selectedQuestion == "Quel style de nage n-est pas autorise aux Jeux olympiques ?") {
vraag49();
}
else if (selectedQuestion == "Quelle equipe a remporte le premier match NBA en 1946 ?") {
vraag50();
}}

void vraag1() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "    Serena Williams <|> Margaret Court";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag1A();
}

void vraag1A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
vraag1A();
}

void vraag2() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "    54 <|> 88";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag2A();
}

void vraag2A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
vraag2A();
}

void vraag3() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   Un mechancete <|> un murmure";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag3A();
}

void vraag3A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
vraag3A();
}

void vraag4() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   le grand fessier <|> la langue";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag4A();
}

void vraag4A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
vraag4A();
}

void vraag5() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   La paruline a joues noires <|> Le colibri de Elena";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag5A();
}

void vraag5A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
vraag5A();
}

void vraag6() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   Blanche-Neige et les Sept Nains <|> Fleurs et arbres";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag6A();
}

void vraag6A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
vraag6A();
}

void vraag7() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   1972 <|> 1974";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag7A();
}

void vraag7A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
vraag7A();
}

void vraag8() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   1964 <|> 1967";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag8A();
}

void vraag8A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
vraag8A();
}

void vraag9() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   10x10 <|> 15x15";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag9A();
}

void vraag9A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
vraag9A();
}

void vraag10() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   6 <|> 7";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag10A();
}

void vraag10A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
vraag10A();
}

void vraag11() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   Le bolet de celeri <|> La barbe-de-bouc";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag11A();
}

void vraag11A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
vraag11A();
}

void vraag12() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   graminees <|> buissons";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag12A();
}

void vraag12A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
vraag12A();
}

void vraag13() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   4 petales <|> 3 petales";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag13A();
}

void vraag13A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
vraag13A();
}

void vraag14() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   21 septembre <|> 21 juin";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag14A();
}

void vraag14A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
vraag14A();
}

void vraag15() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   Droite <|> Gauche";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag15A();
}

void vraag15A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
vraag15A();
}

void vraag16() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   D <|> L";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag16A();
}

void vraag16A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
vraag16A();
}

void vraag17() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   citadelle doree <|> le chateau rouge";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag17A();
}

void vraag17A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
vraag17A();
}

void vraag18() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   ses grottes <|> ses terres marecageuses";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag18A();
}

void vraag18A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
vraag18A();
}

void vraag19() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   Le nom de la fille de lacreatrice <|> Le nom une chanteuse populaire.";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag19A();
}

void vraag19A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
triviaWon();
matrix.renderBitmap(frame, 8, 12);
return;
}}
vraag19A();
}

void vraag20() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   1910 <|> 1940";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag20A();
}

void vraag20A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
vraag20A();
}

void vraag21() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   Le Nil <|> Le Amazone";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag21A();
}

void vraag21A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
vraag21A();
}

void vraag22() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   ocean Atlantique <|> ocean Pacifique";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag22A();
}

void vraag22A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
vraag22A();
}

void vraag23() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   Groenland <|> Madagascar";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag23A();
}

void vraag23A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
vraag23A();
}

void vraag24() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   Reykjavik <|> Oslo";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag24A();
}

void vraag24A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
vraag24A();
}

void vraag25() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   Nigeria <|> Rwanda";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag25A();
}

void vraag25A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
vraag25A();
}

void vraag26() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   Chine <|> Italie";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag26A();
}

void vraag26A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
vraag26A();
}

void vraag27() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   Mont Semeru <|> Mont Bromo";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag27A();
}

void vraag27A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
vraag27A();
}

void vraag28() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   In Varietate Concordia <|> E pluribus unum";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag28A();
}

void vraag28A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
vraag28A();
}

void vraag29() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   Bill Gates <|> Tim Berners-Lee";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag29A();
}

void vraag29A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
vraag29A();
}

void vraag30() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   Bresil <|> Uruguay";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag30A();
}

void vraag30A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
vraag30A();
}

void vraag31() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   Espagnol <|> Portugais";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag31A();
}

void vraag31A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
vraag31A();
}

void vraag32() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   Claude Monet <|> Pablo Picasso";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag32A();
}

void vraag32A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
vraag32A();
}

void vraag33() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   Le Caire <|> Lagos";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag33A();
}

void vraag33A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
vraag33A();
}

void vraag34() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   Invasion de la Pologne <|> Assassinat de archiduc Franz Ferdinand";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag34A();
}

void vraag34A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
vraag34A();
}

void vraag35() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   Hamlet <|> Othello";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag35A();
}

void vraag35A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
vraag35A();
}

void vraag36() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   Burj Khalifa <|> Shanghai Tower";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag36A();
}

void vraag36A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
vraag36A();
}

void vraag37() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   Toronto <|> Ottawa";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag37A();
}

void vraag37A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
vraag37A();
}

void vraag38() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   Mark Twain <|> Herman Melville";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag38A();
}

void vraag38A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
vraag38A();
}

void vraag39() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   Lac Superieur <|> Lac Michigan";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag39A();
}

void vraag39A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
vraag39A();
}

void vraag40() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   Indonesie <|> Philippines";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag40A();
}

void vraag40A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
vraag40A();
}

void vraag41() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   Victor Hugo <|> Charles Baudelaire";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag41A();
}

void vraag41A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
vraag41A();
}

void vraag42() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   Louis Pasteur <|> Alexander Fleming";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag42A();
}

void vraag42A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
vraag42A();
}

void vraag43() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   Bresil <|> Argentine";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag43A();
}

void vraag43A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
vraag43A();
}

void vraag44() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   Mesopotamie <|> Egypte ancienne";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag44A();
}

void vraag44A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
vraag44A();
}

void vraag45() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   Pierce Brosnan <|> Daniel Craig";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag45A();
}

void vraag45A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
vraag45A();
}

void vraag46() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   The American Dream <|> In God We Trust";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag46A();
}

void vraag46A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
vraag46A();
}

void vraag47() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   Springfield <|> Nashville";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag47A();
}

void vraag47A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
vraag47A();
}

void vraag48() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   Claude Francois <|> Frank Alamo";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag48A();
}

void vraag48A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
vraag48A();
}

void vraag49() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   Papillon <|> Pagaie pour chien";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag49A();
}

void vraag49A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
vraag49A();
}

void vraag50() {
digitalWrite(green_led, LOW);
digitalWrite(orange_led, HIGH);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(500);
String messagef = "   Toronto Huskies <|> New York Knicks";
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
matrix.renderBitmap(frame, 8, 12);
delay(200);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
vraag50A();
}

void vraag50A(){
int sensorValue = digitalRead(9);
delay(100);
joystick_pos3 = analogRead(A0) - 512;
if (joystick_pos3 > 0) {
menuOption2();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaWon();
return;
}}
else {
menuOption1();
matrix.renderBitmap(frame, 8, 12);
if (sensorValue == LOW) {
clearscreen();
matrix.renderBitmap(frame, 8, 12);
tone(buzzer, NOTE_G4);
delay(250);
noTone(buzzer);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
matrix.loadSequence(animation);
matrix.play();
delay(1000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
triviaOver();
return;
}}
vraag50A();
}

void triviaWon() {
digitalWrite(RPin, HIGH);
delay(200);
tone(buzzer, NOTE_D4);
delay(100);
tone(buzzer, NOTE_B4);
delay(200);
noTone(buzzer);
delay(200);
firework6();
firework11();
firework15();
firework21();
firework23();
firework26();
firework30();
firework34();
firework36();
delay(200);
String messagef2 = "   -Reponse correcte-";
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(100);
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef2);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
delay(100);
u8g2.clear(); 
digitalWrite(RPin, RState);
delay(200);
leftEye();
rightEye();
nose();
mouth();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
wink();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
leftEye();
matrix.renderBitmap(frame, 8, 12);
delay(500);
}

void triviaOver() {
digitalWrite(green_led, LOW);
digitalWrite(red_led, HIGH);
delay(200);
over();
delay(500);
String messagef2 = "   -Mauvaise reponse-";
tone(buzzer, NOTE_D4);
delay(100);
tone(buzzer, NOTE_B4);
delay(200);
noTone(buzzer);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(100);
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(messagef2);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
delay(500);
digitalWrite(red_led, LOW);
digitalWrite(green_led, HIGH);
u8g2.clear(); 
delay(200);
leftEye();
rightEye();
nose();
mouth();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
wink();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
leftEye();
matrix.renderBitmap(frame, 8, 12);
delay(500);
}

void genSqr_Angle(){
#define mn 22
#define scaledist 22
#define scaleang 16
for (int i = 0; i < NUM_COLS; i++) {
for (int j = 0; j < NUM_ROWS; j++) {
int temp = pow((i-NUM_COLS/2)*mn,2)+pow((j-NUM_ROWS/2)*mn,2);    
byte distance = temp? 255-sqrt16(temp):255;
dist [j*NUM_COLS+i] = distance/scaledist ; 
byte angle = (NUM_COLS/2)*(atan2((i-NUM_COLS/2), (j-NUM_ROWS/2)) / PI);
// ang [j*NUM_COLS+i] = angle/scaleang;
ang [j*NUM_COLS+i] = angle;
}}}

void generateTex(){
CRGBPalette16 myPal = firepal;
uint16_t a = millis()/4;
for (int i = 0; i < NUM_COLS; i++) {
for (int j = 0; j < NUM_ROWS; j++) {
tex[j][i] = ColorFromPalette(myPal, 
qsub8(inoise8(i * 60, j * 60+a , a / 2), abs8(j * 255 / 18))+20, 255);
}}}

void tunnel(uint16_t xoffset, uint16_t yoffset){
for (int j = 0; j < NUM_ROWS; j++){ 
int yindex = j*NUM_COLS;
for (int i = 0; i < NUM_COLS; i++) {
byte u = dist [yindex+i];
byte v = ang  [yindex+i];
CRGB color =  tex[(u+xoffset)%texSizeX][(v+yoffset)%texSizeY];
leds[XY(i,j)] = color;
}}}

void generateCHSVlut(){
for (int j= 0; j<256; j++) 
chsvLut[j] = HeatColor(j/1.4);  //256 pallette color
}

void generatebump (){
int t=millis()/4;
int index=0;
for (byte j= 0; j< (NUM_ROWS+2); j++) {
for (byte i=0; i< (NUM_COLS+2); i++) {                     
byte col = (inoise8_raw(i * 25, j *25,t))/2; 
bump[index++] = col;
}}} 

void Bumpmap(){
int yindex=(NUM_COLS+3);
int8_t vly=-(NUM_ROWS/2+1);
for (byte y = 0; y < NUM_ROWS; y++) { 
++vly;
int8_t vlx=-(NUM_COLS/2+1);
for (byte x = 0; x < NUM_COLS; x++) {
++vlx;
int8_t nx=bump[x+yindex+1]-bump[x+yindex-1];
int8_t ny=bump[x+yindex+(NUM_COLS+2)]-bump[x+yindex-(NUM_COLS+2)];
byte difx=abs8(vlx*7-nx);
byte dify=abs8(vly*7-ny);
int temp = difx*difx+dify*dify;
int col = 255-temp/13;
if (col<0) col=0;
leds[XY(x,y)] = chsvLut[col]; //thx satubarosu ))
}
yindex+=(NUM_COLS+2);
}}

void Fire(){
int ahoure = timeClient.getHours();
int aminute = timeClient.getMinutes();
if (ahoure >= 0 && ahoure < 8) {
FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setDither(0);
FastLED.setBrightness(ledBrightness);
FastLED.show();
EVERY_N_MILLIS(100){
for (int8_t row=NUM_ROWS-1; row>=0; row--){
for (int8_t col=0; col<NUM_COLS; col++){
if (leds[getIndex(col, row)] == CRGB(175,255,175)){
leds[getIndex(col, row)] = CRGB(27,130,39);
if (row < NUM_ROWS-1) leds[getIndex(col, row+1)] = CRGB(175,255,175);
}}}
for(int i = 0; i < NUM_LEDS; i++) {
if (leds[i].g != 255) leds[i].nscale8(192);
}
bool emptyScreen = true;
for(int i = 0; i < NUM_LEDS; i++) {
if (leds[i]){
emptyScreen = false;
break;
}}
if (random8(3) == 0 || emptyScreen) {
int8_t spawnX = random8(NUM_COLS);
leds[getIndex(spawnX, 0)] = CRGB(175,255,175 );
}
FastLED.show();
}}
else {
if (ahoure >= 8 && ahoure < 12) {
read_response2();
FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
FastLED.setBrightness(BRIGHTNESS2);
static uint16_t xoffset =24;
static uint16_t yoffset =0;
generateTex(); 
tunnel(xoffset, yoffset);
LEDS.show();
}
else {
if (ahoure >= 12 && ahoure < 14) {
read_response2();
FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
FastLED.setBrightness(BRIGHTNESS3);
generatebump();
Bumpmap();
FastLED.show();
}
else {
if (ahoure >= 19 && ahoure <= 23) {
read_response2();
FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
FastLED.setMaxPowerInVoltsAndMilliamps(5, MAX_POWER_MILLIAMPS);
FastLED.setBrightness(BRIGHTNESS);
int scalexy = 60; 
float speed = 0.7;
float a = millis()*speed;
for (int i = 0; i < NUM_COLS; i++) {
for (int j = 0; j < NUM_ROWS; j++) {
leds[XY(i, j)] = 
ColorFromPalette(myPal, qsub8(inoise8(i * scalexy, j * scalexy + (int)a, (int)a / 2), abs8(j - (NUM_ROWS - 1)) * 255 / (NUM_ROWS + 2)), 255);
}}
FastLED.show();
}
else {
read_response2();
FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
FastLED.setBrightness(BRIGHTNESS2);
static uint16_t xoffset =24;
static uint16_t yoffset =0;
generateTex(); 
tunnel(xoffset, yoffset);
LEDS.show();
}}}}}

void openmeteo(){
clearscreen();
matrix.renderBitmap(frame, 8, 12);
delay(200);
const char text123[] = "=";
matrix.textFont(Font_4x6);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(text123);
matrix.endText();
matrix.endDraw();
delay(200);
const char text124[] = "=>";
matrix.textFont(Font_4x6);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(text124);
matrix.endText();
matrix.endDraw();
delay(200);
const char text125[] = "=>>";
matrix.textFont(Font_4x6);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(text125);
matrix.endText();
matrix.endDraw();
image0();
image1();
image2();
image3();
image4();
image5();
image6();
image7();
image8();
image9();
image0();
image1();
image2();
image3();
image4();
image5();
image6();
image7();
image8();
image9();
u8g2.clear();
delay(250);
read_response();
delay(500);
leftEye();
rightEye();
nose();
mouth();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
wink();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
leftEye();
matrix.renderBitmap(frame, 8, 12);
delay(500);
}

void read_response() {
u8g2.clear();
uint32_t received_data_num = 0;
String payload = "";
bool jsonDetected = false;
while (client.available()) {
char c = client.read();
if ('{' == c) {
jsonDetected = true;
}
if (jsonDetected) {
payload += c;
}
received_data_num++;
}
if (jsonDetected) {
DynamicJsonDocument root(3000);
DeserializationError error = deserializeJson(root, payload);
if (error) {
Serial.print("Deserialization failed with code: ");
Serial.println(error.c_str());
return;
}
float latitude = (float)(root["latitude"]);
float longitude = (float)(root["longitude"]);
float elevation = (float)(root["elevation"]);
float temperature_2m = (float)(root["current"]["temperature_2m"]);
float apparent_temperature = (float)(root["current"]["apparent_temperature"]);
int relative_humidity_2m = root["current"]["relative_humidity_2m"];
float pressure_msl = (float)(root["current"]["pressure_msl"]);
float surface_pressure = (float)(root["current"]["surface_pressure"]);
float wind_speed_10m = root["current"]["wind_speed_10m"];
int wind_direction_10m = root["current"]["wind_direction_10m"];
float wind_gusts_10m = root["current"]["wind_gusts_10m"];
Serial.println(payload);
displayWeatherData(elevation, temperature_2m, apparent_temperature);
delay(5000);
displayWeatherData2(latitude, longitude, relative_humidity_2m);
delay(5000);
displayWeatherData3(wind_speed_10m, wind_direction_10m, wind_gusts_10m);
delay(5000);
displayWeatherData4(pressure_msl, surface_pressure);
}
delay(5000);
clearscreen();
matrix.renderBitmap(frame, 8, 12);
u8g2.clear(); 
}

void read_response2() {
uint32_t received_data_num2 = 0;
String payload2 = "";
bool jsonDetected = false;
while (clientssl.available()) {
char c = clientssl.read();
if ('{' == c) {
jsonDetected = true;
}
if (jsonDetected) {
payload2 += c;
}
received_data_num2++;
}
if (jsonDetected) {
DynamicJsonDocument root2(3000);
DeserializationError error = deserializeJson(root2, payload2);
if (error) {
Serial.print("Deserialization failed with code: ");
Serial.println(error.c_str());
return;
}
int startIndex = payload2.indexOf("<setup>") + String("<setup>").length();
int endIndex = payload2.indexOf("</setup>");
int startIndex2 = payload2.indexOf("<delivery>") + String("<delivery>").length();
int endIndex2 = payload2.indexOf("</delivery>");
u8g2.clearBuffer();
u8g2.firstPage();
do {
if (startIndex != -1 && endIndex != -1 && endIndex > startIndex) {
u8g2.setCursor(0, 13);
u8g2.setFont(u8g2_font_8x13_tf);
printWrappedText(payload2.substring(startIndex, endIndex), 128, 14);
if (startIndex2 != -1 && endIndex2 != -1 && endIndex2 > startIndex2) {
u8g2.setCursor(0, 88);
u8g2.setFont(u8g2_font_8x13_tf);
printWrappedText2(payload2.substring(startIndex2, endIndex2), 128, 14);
}
u8g2.sendBuffer();
} 
else {
Serial.println("Geen setup gegevens gevonden.");
}
if (!root2["error"]) {
} else {
Serial.println("Er is een fout in de JSON: error is true.");
}} 
while (u8g2.nextPage());
}}

void botje(){
u8g2.firstPage();
do {
u8g2.drawXBMP(0, 0, 128, 128, botje_128x128px);} 
while ( u8g2.nextPage() );
}
  
void skynet(){
u8g2.firstPage();
do {
u8g2.drawXBMP(0, 0, 128, 128, skyneti);} 
while ( u8g2.nextPage() );
}
  
void hello(){
u8g2.firstPage();
do {
u8g2.drawXBMP(0, 0, 128, 128, hellohello);} 
while ( u8g2.nextPage() );
}
  
void over(){
u8g2.firstPage();
do {
u8g2.drawXBMP(0, 0, 128, 128, overi);} 
while ( u8g2.nextPage() );
}

void over2(){
u8g2.firstPage();
do {
u8g2.drawXBMP(0, 0, 128, 128, over2i);} 
while ( u8g2.nextPage() );
}

void image0(){
u8g2.firstPage();
do {
u8g2.drawXBMP(0, 0, 128, 128, image0i);
} 
while ( u8g2.nextPage() );
}

void image1(){
u8g2.firstPage();
do {
u8g2.drawXBMP(0, 0, 128, 128, image1i);
} 
while ( u8g2.nextPage() );
}

void image2(){
u8g2.firstPage();
do {
u8g2.drawXBMP(0, 0, 128, 128, image2i);
} 
while ( u8g2.nextPage() );
}

void image3(){
u8g2.firstPage();
do {
u8g2.drawXBMP(0, 0, 128, 128, image3i);
} 
while ( u8g2.nextPage() );
}

void image4(){
u8g2.firstPage();
do {
u8g2.drawXBMP(0, 0, 128, 128, image4i);
} 
while ( u8g2.nextPage() );
}

void image5(){
u8g2.firstPage();
do {
u8g2.drawXBMP(0, 0, 128, 128, image5i);
} 
while ( u8g2.nextPage() );
}

void image6(){
u8g2.firstPage();
do {
u8g2.drawXBMP(0, 0, 128, 128, image6i);
} 
while ( u8g2.nextPage() );
}

void image7(){
u8g2.firstPage();
do {
u8g2.drawXBMP(0, 0, 128, 128, image7i);
} 
while ( u8g2.nextPage() );
}

void image8(){
u8g2.firstPage();
do {
u8g2.drawXBMP(0, 0, 128, 128, image8i);
} 
while ( u8g2.nextPage() );
}

void image9(){
u8g2.firstPage();
do {
u8g2.drawXBMP(0, 0, 128, 128, image9i);
} 
while ( u8g2.nextPage() );
}

void flappy1(){
u8g2.firstPage();
do {
u8g2.drawXBMP(0, 0, 128, 128, flappy1i);
} 
while ( u8g2.nextPage() );
}

void firework6(){
u8g2.firstPage();
do {
u8g2.drawXBMP(0, 0, 128, 128, firework6i);
} 
while ( u8g2.nextPage() );
}

void firework11(){
u8g2.firstPage();
do {
u8g2.drawXBMP(0, 0, 128, 128, firework11i);
} 
while ( u8g2.nextPage() );
}

void firework15(){
u8g2.firstPage();
do {
u8g2.drawXBMP(0, 0, 128, 128, firework15i);
} 
while ( u8g2.nextPage() );
}

void firework21(){
u8g2.firstPage();
do {
u8g2.drawXBMP(0, 0, 128, 128, firework21i);
} 
while ( u8g2.nextPage() );
}

void firework23(){
u8g2.firstPage();
do {
u8g2.drawXBMP(0, 0, 128, 128, firework23i);
} 
while ( u8g2.nextPage() );
}

void firework26(){
u8g2.firstPage();
do {
u8g2.drawXBMP(0, 0, 128, 128, firework26i);
} 
while ( u8g2.nextPage() );
}

void firework30(){
u8g2.firstPage();
do {
u8g2.drawXBMP(0, 0, 128, 128, firework30i);
} 
while ( u8g2.nextPage() );
}

void firework34(){
u8g2.firstPage();
do {
u8g2.drawXBMP(0, 0, 128, 128, firework34i);
} 
while ( u8g2.nextPage() );
}

void firework36(){
u8g2.firstPage();
do {
u8g2.drawXBMP(0, 0, 128, 128, firework36i);
} 
while ( u8g2.nextPage() );
}

void snake1(){
u8g2.firstPage();
do {
u8g2.drawXBMP(0, 0, 128, 128, snake1i);
} 
while ( u8g2.nextPage() );
}

void clockmatrix() {
timeClient.update();
time_t epochTime3 = timeClient.getEpochTime();
unsigned long epochTime4 = timeClient.getEpochTime();
while (epochTime4 < 1707219755) {
epochTime4 = timeClient.getEpochTime();
delay(25);
}
struct tm *ptm = gmtime ((time_t *)&epochTime3);
int aYear = ptm->tm_year + 1900;
int amonth = ptm->tm_mon + 1;
int monthDay = ptm->tm_mday;
int aday = timeClient.getDay();
int ahoure = timeClient.getHours();
int aMinute = timeClient.getMinutes();
int aSeconds = ptm->tm_sec;
char timestamp84[50];
if (ahoure < 10) {
if (aMinute < 10) {
snprintf(timestamp84, 50, " 0%d:0%d", ahoure, aMinute);
}
else if (ahoure < 10 && aMinute >= 10) {
snprintf(timestamp84, 50, " 0%d:%d", ahoure, aMinute);
} 
else {
snprintf(timestamp84, 50, " %d:%d", ahoure, aMinute);
}}
else {
if (aMinute < 10) {
snprintf(timestamp84, 50, " %d:0%d", ahoure, aMinute);
}
else {
snprintf(timestamp84, 50, " %d:%d", ahoure, aMinute);
}}
matrix2.setTextSize(1);
matrix2.setTextWrap(false);
matrix2.setTextColor(LED_ON);
matrix2.setRotation(1);
for (int8_t x=7; x>=-36; x--) {
matrix2.clear();
matrix2.setCursor(x,0);
matrix2.setBrightness(10);
matrix2.print(timestamp84);
matrix2.writeDisplay();
delay(25);
}}

void clockmatrix2() {
timeClient.update();
time_t epochTime3 = timeClient.getEpochTime();
unsigned long epochTime4 = timeClient.getEpochTime();
while (epochTime4 < 1707219755) {
epochTime4 = timeClient.getEpochTime();
delay(25);
}
struct tm *ptm = gmtime ((time_t *)&epochTime3);
int aYear = ptm->tm_year + 1900;
int amonth = ptm->tm_mon + 1;
int monthDay = ptm->tm_mday;
int aday = timeClient.getDay();
int ahoure = timeClient.getHours();
int aMinute = timeClient.getMinutes();
int aSeconds = ptm->tm_sec;
char timestamp84[50];
if (ahoure < 10) {
if (aMinute < 10) {
snprintf(timestamp84, 50, " 0%d:0%d", ahoure, aMinute);
}
else if (ahoure < 10 && aMinute >= 10) {
snprintf(timestamp84, 50, " 0%d:%d", ahoure, aMinute);
} 
else {
snprintf(timestamp84, 50, " %d:%d", ahoure, aMinute);
}}
else {
if (aMinute < 10) {
snprintf(timestamp84, 50, " %d:0%d", ahoure, aMinute);
}
else {
snprintf(timestamp84, 50, " %d:%d", ahoure, aMinute);
}}
matrix2.setTextSize(1);
matrix2.setTextWrap(false);
matrix2.setTextColor(LED_ON);
matrix2.setRotation(1);
for (int8_t x=7; x>=-36; x--) {
matrix2.clear();
matrix2.setCursor(x,0);
matrix2.setBrightness(0.1);
matrix2.print(timestamp84);
matrix2.writeDisplay();
delay(25);
}}

void setup() {
Serial.begin(115200);
FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
FastLED.clear(true);
matrix2.begin(0x70);
dht.begin();
bmp.begin();
MQ.begin();
u8g2.begin();
u8g2.clearBuffer();
u8g2.setContrast(128);
u8g2.enableUTF8Print();
pinMode(SW, INPUT_PULLUP);
pinMode(RPin, OUTPUT);
pinMode(A0, INPUT);
pinMode(A1, INPUT);
pinMode (green_led, OUTPUT);
pinMode (orange_led, OUTPUT);
pinMode (red_led, OUTPUT);
digitalWrite(green_led, LOW);
digitalWrite(orange_led, LOW);
digitalWrite(red_led, HIGH);
digitalWrite(RPin, RState);
RTC.begin();
botje();
matrix.begin();
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(30);
const char text1[] = "   Synchronisation Skynet";
matrix.textFont(Font_4x6);
matrix.beginText(12, 1, 0xFFFFFF);
matrix.println(text1);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
int connectionCounter = 0;
while (status != WL_CONNECTED) {
status = WiFi.begin(ssid, pass);
delay(250);
if ((connectionCounter % 10) == 0) {
}
connectionCounter++;
}
digitalWrite(red_led, LOW);
digitalWrite(orange_led, HIGH);
matrix.loadSequence(animation2);
matrix.play();
delay(1250);
u8g2.clear();
skynet();
IPAddress ip = WiFi.localIP();
char ipString[20];
ip.toString().toCharArray(ipString, 20);
long rssi = WiFi.RSSI();
char rssiString[20];
sprintf(rssiString, " %d%s", rssi, "dbm.");
char timestamp8[45];
snprintf(timestamp8, 45, "   Connexion Skynet: %s  %s", ipString, rssiString);
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(40);
matrix.textFont(Font_5x7);
matrix.beginText(12, 1, 0xFFFFFF);
matrix.println(timestamp8);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
timeClient.begin();
timeClient.setTimeOffset(7200);
timeClient.update();
RTCTime arduino;
arduino.setUnixTime(timeClient.getEpochTime());
RTC.setTime(arduino);
delay(250);
digitalWrite(orange_led, LOW);
digitalWrite(green_led, HIGH);
u8g2.clear(); 
hello();
setupwelcome();
u8g2.clear(); 
song();
genSqr_Angle();
generateCHSVlut();
}

void loop() {
int choure = timeClient.getHours();
int cminute = timeClient.getMinutes();
unsigned long currentMillis = millis();
unsigned long currentMillis2 = millis();
if (choure == 0 && cminute == 1) {
u8g2.clear();
}
if (currentMillis - lastConnectionTime > postingInterval) {
http_request();
}
if (choure >= 0 && choure < 8) {
Fire();
sw2();
face();
if (!client.connected()) {
client.stop();
}
if (!clientssl.connected()) {
clientssl.stop();
}}
else {
if (choure >= 19 && choure <= 23) {
if (currentMillis - lastConnectionTime2 > postingInterval2) {
http_request2();
}
Fire();
sw2();
face();
if (!client.connected()) {
client.stop();
}
if (!clientssl.connected()) {
clientssl.stop();
}
if (currentMillis2 - previousMillis2 >= interval2) {
previousMillis2 = currentMillis2; 
clockmatrix2();
}}
else {
if (currentMillis - lastConnectionTime2 > postingInterval2) {
http_request2();
}
Fire();
sw2();
face();
if (!client.connected()) {
client.stop();
}
if (!clientssl.connected()) {
clientssl.stop();
}
if (currentMillis - previousMillis >= interval) {
previousMillis = currentMillis; 
clockmatrix();
}}}}

void http_request() {
if (client.connect(server, 80)) {
client.println("GET /v1/forecast?latitude=50.6337&longitude=5.5675&current=temperature_2m,relative_humidity_2m,apparent_temperature,is_day,precipitation,rain,showers,snowfall,weather_code,cloud_cover,pressure_msl,surface_pressure,wind_speed_10m,wind_direction_10m,wind_gusts_10m&timezone=Europe%2FBerlin&forecast_days=1 HTTP/1.1");
client.println("Host: api.open-meteo.com");
client.println("la connexion a échoué");
client.println();
lastConnectionTime = millis();
} 
else {
Serial.println("connection failed");
}}

void http_request2() {
if (clientssl.connect(server2, 443)) {
clientssl.println("GET /joke/Any?lang=fr&format=xml&type=twopart HTTP/1.1");
clientssl.println("Host: v2.jokeapi.dev");
clientssl.println("Connection: close");
clientssl.println();
lastConnectionTime2 = millis();
} 
else {
Serial.println("connection failed");
}}

void printWrappedText(String text, int screenWidth, int lineHeight) {
int cursorY = 13;
String currentLine = "";
for (int i = 0; i < text.length(); i++) {
char c = text.charAt(i);
currentLine += c;
if (u8g2.getStrWidth(currentLine.c_str()) > screenWidth) {
u8g2.setCursor(0, cursorY);
u8g2.print(currentLine);
cursorY += lineHeight;
currentLine = ""; 
currentLine += c;
}}
if (currentLine.length() > 0) {
u8g2.setCursor(0, cursorY);
u8g2.print(currentLine);
}}

void printWrappedText2(String text, int screenWidth, int lineHeight) {
int cursorY = 88;
String currentLine = "";
for (int i = 0; i < text.length(); i++) {
char c = text.charAt(i);
currentLine += c;
if (u8g2.getStrWidth(currentLine.c_str()) > screenWidth) {
u8g2.setCursor(0, cursorY);
u8g2.print(currentLine);
cursorY += lineHeight;
currentLine = ""; 
currentLine += c;
}}
if (currentLine.length() > 0) {
u8g2.setCursor(0, cursorY);
u8g2.print(currentLine);
}}

void displayWeatherData(float elevation, float temperature_2m, float apparent_temperature) {
u8g2.clearBuffer();
u8g2.firstPage();
do {
u8g2.setCursor(30, 15);
u8g2.setFont(u8g2_font_ncenB14_tr);           
u8g2.print("-Liege-");
u8g2.setCursor(0, 32);
u8g2.setFont(u8g2_font_ncenB08_tr);           
u8g2.print("Elevation");
u8g2.setCursor(0, 50);
u8g2.setFont(u8g2_font_ncenB10_tr);           
u8g2.print(elevation);
u8g2.setCursor(40, 50);
u8g2.setFont(u8g2_font_ncenB08_tr);           
u8g2.print("m");
u8g2.setCursor(0, 63);
u8g2.setFont(u8g2_font_ncenB08_tr);           
u8g2.print("Temp");
u8g2.setCursor(0, 80);
u8g2.setFont(u8g2_font_ncenB10_tr);           
u8g2.print(temperature_2m);
u8g2.setCursor(40, 80);
u8g2.setFont(u8g2_font_ncenB08_tr);           
u8g2.print("C");
u8g2.setCursor(0, 93);
u8g2.setFont(u8g2_font_ncenB08_tr);           
u8g2.print("Temp app");
u8g2.setCursor(0, 110);
u8g2.setFont(u8g2_font_ncenB10_tr);           
u8g2.print(apparent_temperature);
u8g2.setCursor(40, 110);
u8g2.setFont(u8g2_font_ncenB08_tr);           
u8g2.print("C");
u8g2.sendBuffer();
}
while ( u8g2.nextPage() );
}

void displayWeatherData2(float latitude, float longitude, int relative_humidity_2m) {
u8g2.clearBuffer();
u8g2.firstPage();
do {
u8g2.setCursor(30, 15);
u8g2.setFont(u8g2_font_ncenB14_tr);           
u8g2.print("-Liege-");
u8g2.setCursor(0, 32);
u8g2.setFont(u8g2_font_ncenB08_tr);           
u8g2.print("Latitude");
u8g2.setCursor(0, 50);
u8g2.setFont(u8g2_font_ncenB10_tr);           
u8g2.print(latitude);
u8g2.setCursor(0, 63);
u8g2.setFont(u8g2_font_ncenB08_tr);           
u8g2.print("Longitude");
u8g2.setCursor(0, 80);
u8g2.setFont(u8g2_font_ncenB10_tr);           
u8g2.print(longitude);
u8g2.setCursor(0, 93);
u8g2.setFont(u8g2_font_ncenB08_tr);           
u8g2.print("Humidite");
u8g2.setCursor(0, 110);
u8g2.setFont(u8g2_font_ncenB10_tr);           
u8g2.print(relative_humidity_2m);
u8g2.setCursor(20, 110);
u8g2.setFont(u8g2_font_ncenB08_tr);           
u8g2.print("%");
u8g2.sendBuffer();
}
while ( u8g2.nextPage() );
}

void displayWeatherData3(float wind_speed_10m, int wind_direction_10m, float wind_gusts_10m) {
u8g2.clearBuffer();
u8g2.firstPage();
do {
u8g2.setCursor(30, 15);
u8g2.setFont(u8g2_font_ncenB14_tr);           
u8g2.print("-Liege-");
u8g2.setCursor(0, 32);
u8g2.setFont(u8g2_font_ncenB08_tr);           
u8g2.print("Vit. vent");
u8g2.setCursor(0, 50);
u8g2.setFont(u8g2_font_ncenB10_tr);           
u8g2.print(wind_speed_10m);
u8g2.setCursor(40, 50);
u8g2.setFont(u8g2_font_ncenB08_tr);           
u8g2.print("Km/h");
u8g2.setCursor(0, 63);
u8g2.setFont(u8g2_font_ncenB08_tr);           
u8g2.print("Dir. vent");
u8g2.setCursor(0, 80);
u8g2.setFont(u8g2_font_ncenB10_tr);           
u8g2.print(wind_direction_10m);
u8g2.setCursor(0, 93);
u8g2.setFont(u8g2_font_ncenB08_tr);           
u8g2.print("Raf. vent");
u8g2.setCursor(0, 110);
u8g2.setFont(u8g2_font_ncenB10_tr);           
u8g2.print(wind_gusts_10m);
u8g2.setCursor(40, 110);
u8g2.setFont(u8g2_font_ncenB08_tr);           
u8g2.print("Km/h");
u8g2.sendBuffer();
}
while ( u8g2.nextPage() );
}

void displayWeatherData4(float pressure_msl, float surface_pressure) {
u8g2.clearBuffer();
u8g2.firstPage();
do {
u8g2.setCursor(30, 15);
u8g2.setFont(u8g2_font_ncenB14_tr);           
u8g2.print("-Liege-");
u8g2.setCursor(0, 32);
u8g2.setFont(u8g2_font_ncenB08_tr);           
u8g2.print("pression n/m");
u8g2.setCursor(0, 50);
u8g2.setFont(u8g2_font_ncenB10_tr);           
u8g2.print(pressure_msl);
u8g2.setCursor(60, 50);
u8g2.setFont(u8g2_font_ncenB08_tr);           
u8g2.print("hPa");
u8g2.setCursor(0, 63);
u8g2.setFont(u8g2_font_ncenB08_tr);           
u8g2.print("pression");
u8g2.setCursor(0, 80);
u8g2.setFont(u8g2_font_ncenB10_tr);           
u8g2.print(surface_pressure);
u8g2.setCursor(60, 80);
u8g2.setFont(u8g2_font_ncenB08_tr);           
u8g2.print("hPa");
u8g2.sendBuffer();
}
while ( u8g2.nextPage() );
}
