#include "Wire.h"
#include "OneWire.h"
#include "DallasTemperature.h"
#include "U8g2lib.h"
#include "ArduinoGraphics.h"
#include "start.h"
U8G2_SH1107_SEEED_128X128_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
#define ANALOG_PIN A2
#define PIN_ANTENNA A0
#define PIN_R 4
#define PIN_G 5
#define PIN_B 6
#define CHECK_DELAY 500
#define lmillis() ((long)millis())
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
float lastTemperature = 0.0;
int lastEmfValue = 0;
int lastEmfValue2 = 0;
int emfValue2 = 0;

void start_setup(){
u8g2.firstPage();
do {
u8g2.drawXBMP(0, 0, 128, 128, start_1);} 
while ( u8g2.nextPage() );
}

void setup(){
Serial.begin(9600);
pinMode(PIN_ANTENNA, INPUT);
pinMode(PIN_R, OUTPUT);
pinMode(PIN_B, OUTPUT);
pinMode(PIN_G, OUTPUT);
digitalWrite(PIN_R, LOW);
digitalWrite(PIN_B, LOW);
digitalWrite(PIN_G, LOW);
u8g2.begin();
u8g2.clearBuffer();
u8g2.setContrast(250);
u8g2.enableUTF8Print();
u8g2.clear();
start_setup();
sensors.begin();
delay(5000);
}

void showReadings(int emfValue) {
emfValue2 = constrain(analogRead(ANALOG_PIN), 0, 1023);
sensors.requestTemperatures();
float currentTemperature = sensors.getTempCByIndex(0); 
if (abs(currentTemperature - lastTemperature) >= 0.5) {
digitalWrite(PIN_G, HIGH);
delay(200); 
digitalWrite(PIN_G, LOW);
}
lastTemperature = currentTemperature;
if (abs(emfValue - lastEmfValue) >= 10) {
digitalWrite(PIN_R, HIGH);
delay(200);
digitalWrite(PIN_R, LOW);
}
lastEmfValue = emfValue; 
if (abs(emfValue2 - lastEmfValue2) >= 10) {
digitalWrite(PIN_B, HIGH);
delay(200);
digitalWrite(PIN_B, LOW);
}
lastEmfValue2 = emfValue2; 
u8g2.clear();
do {
u8g2.drawFrame(3,3,125,28);
u8g2.drawFrame(3,3,125,125);
u8g2.drawFrame(3,72,125,24);
u8g2.setCursor(28 , 24);
u8g2.setFont(u8g2_font_ncenB14_tr);
u8g2.print("-- EMF --");
u8g2.setCursor(55, 49);
u8g2.setFont(u8g2_font_ncenB10_tr);
u8g2.print(emfValue);
u8g2.setCursor(55, 65);
u8g2.setFont(u8g2_font_ncenB10_tr);
u8g2.print(emfValue2);
u8g2.setCursor(15 , 88);
u8g2.setFont(u8g2_font_ncenB08_tr);
u8g2.print("- TEMPERATURE -");
u8g2.setCursor(43 , 116);
u8g2.setFont(u8g2_font_ncenB10_tr);
u8g2.print(currentTemperature);
u8g2.setCursor(83 , 116);
u8g2.setFont(u8g2_font_ncenB10_tr);
u8g2.print("C");
}
while (u8g2.nextPage());
}

void loop() {
static int avgValue = 0, emfValue = 0;
static long nextCheck = 0, emfSum = 0, iterations = 0; 
emfValue = constrain(analogRead(PIN_ANTENNA), 0, 1023);
emfSum += emfValue;
iterations++;
if (lmillis() - nextCheck >= 0) {
avgValue = emfSum / iterations;
emfSum = 0;
iterations = 0;
showReadings(avgValue);
nextCheck = lmillis() + CHECK_DELAY;
}}
