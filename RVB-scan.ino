#include <PCM.h>
#include <PCM_nico.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
#define S1 5
#define S0 6
#define S3 7
#define S2 8
#define OUT 9
const int ledcPin = 10;
const int RPin = A3;
const int GPin = A2;
const int BPin = A1;
const int button2Pin = A0;
int button2State = 0;
int lastButton2State = 0;
unsigned long lastDebounce2Time = 0;
unsigned long debounce2Delay = 50;
int button2Presses = 0;
int redMin = 47;
int redMax = 172;
int greenMin = 46;
int greenMax = 182;
int blueMin = 38;
int blueMax = 143;
int redColor = 0;
int greenColor = 0;
int blueColor = 0;
int redColorp = 0;
int greenColorp = 0;
int blueColorp = 0;
uint16_t frequencyR = 0;
uint16_t frequencyG = 0;
uint16_t frequencyB = 0;
void stop_all() {
digitalWrite(S0, LOW);
digitalWrite(S1, LOW);
digitalWrite(S2, LOW);
digitalWrite(S3, LOW);
}
void read_20() {
digitalWrite(S0, HIGH);
digitalWrite(S1, LOW);
}

void setup() {
Serial.begin(9600);
lcd.init();
startPlayback(PCM_gong, sizeof(PCM_gong));
pinMode(button2Pin, INPUT_PULLUP);
pinMode(ledcPin, OUTPUT);
pinMode(RPin, OUTPUT);
pinMode(GPin, OUTPUT);
pinMode(BPin, OUTPUT);
analogWrite(RPin, 0);
analogWrite(GPin, 0);
analogWrite(BPin, 0);
pinMode(S0, OUTPUT);
pinMode(S1, OUTPUT);
pinMode(S2, OUTPUT);
pinMode(S3, OUTPUT);
pinMode(OUT, INPUT);
lcd.backlight();
delay(250);
lcd.setCursor(0, 0);
lcd.print("   R.V.B.SCAN   ");
lcd.setCursor(0, 1);
lcd.print("  ____________  ");  
delay(3000);
lcd.clear();
delay(500);
lcd.noBacklight();
read_20();
}

void loop() {
int reading2 = digitalRead(button2Pin);
if (reading2 != lastButton2State) {
lastDebounce2Time = millis();
}
if ((millis() - lastDebounce2Time) > debounce2Delay) {
if (reading2 != button2State) {
button2State = reading2;
if (button2State == LOW) {
button2Presses++;
if (button2Presses == 1) {
lcd.clear();
digitalWrite(ledcPin, HIGH);
delay(500);
read_20();
delay(200);
digitalWrite(S2, LOW);
digitalWrite(S3, LOW);
frequencyR = pulseIn(OUT, LOW);
Serial.print("RED = ");
Serial.print(frequencyR);
redColor = map(frequencyR, redMin,redMax,255,0);
redColorp = map(redColor,0,255,0,100);
Serial.print("\t");
delay(200);
digitalWrite(S2, HIGH);
digitalWrite(S3, HIGH);
frequencyG = pulseIn(OUT, LOW);
Serial.print("GREEN = ");
Serial.print(frequencyG);
greenColor = map(frequencyG, greenMin,greenMax,255,0);
greenColorp = map(greenColor,0,255,0,100);
Serial.print("\t");
delay(200);
digitalWrite(S2, LOW);
digitalWrite(S3, HIGH);
frequencyB = pulseIn(OUT, LOW);
Serial.print("BLUE = ");
Serial.println(frequencyB);
blueColor = map(frequencyB, blueMin,blueMax,255,0);
blueColorp = map(blueColor,0,255,0,100);
Serial.println(" ");
delay(200);
stop_all();
delay(200);
digitalWrite(ledcPin, LOW);
lcd.backlight();
delay(500);
Serial.print("RED-RGB = ");
Serial.print(redColor);
Serial.print("\t");
Serial.print("GREEN-RGB = ");
Serial.print(greenColor);
Serial.print("\t");
Serial.print("BLUE-RGB = ");
Serial.println(blueColor);
Serial.println(" ");
analogWrite(RPin, redColor);
analogWrite(GPin, greenColor);
analogWrite(BPin, blueColor);
startPlayback(PCM_gong, sizeof(PCM_gong));
lcd.setCursor(0, 0);
lcd.print("R");
lcd.print(redColor);
lcd.print(" V");
lcd.print(greenColor);
lcd.print(" B");
lcd.print(blueColor);
lcd.setCursor(0, 1);
lcd.print("R");
lcd.print(redColorp);
lcd.print("%");
lcd.print(" V");
lcd.print(greenColorp);
lcd.print("%");
lcd.print(" B");
lcd.print(blueColorp);
lcd.print("%");
}
else if (button2Presses == 2) {
digitalWrite(ledcPin, LOW);
analogWrite(RPin, LOW);
analogWrite(GPin, LOW);
analogWrite(BPin, LOW);
lcd.clear();
delay(500);
lcd.noBacklight();
button2Presses = 0;
}}}}
   lastButton2State = reading2;
}
