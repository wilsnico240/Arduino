#include <Stepper.h>
#include <Wire.h>
#include "Adafruit_VL6180X.h"
Adafruit_VL6180X vl = Adafruit_VL6180X();
const int motorPin1 = 8;
const int motorPin2 = 9;
const int motorPin3 = 10;
const int motorPin4 = 11;
const int in1 = 4;
const int in2 = 3;
const int ena = 2;
const int buttonPin = 5;
const int stepsPerRevolution = 200;
int buttonState = 0;
int lastButtonState = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int buttonPresses = 0;
Stepper stepper(stepsPerRevolution, motorPin1, motorPin3, motorPin2, motorPin4);

void setup() {
Serial.begin(9600);
vl.begin();
pinMode(buttonPin, INPUT_PULLUP);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(ena, OUTPUT);
setupScan();
digitalWrite(in1, LOW);
digitalWrite(in2, LOW);
digitalWrite(motorPin1, LOW);
digitalWrite(motorPin2, LOW);
digitalWrite(motorPin3, LOW);
digitalWrite(motorPin4, LOW);
}

void motor1() {
Backward();
delay(500);
analogWrite(ena, 0);
digitalWrite(in1, LOW);
digitalWrite(in2, LOW);
delay(500);
}

void motor1null() {
Forward();
delay(19975);
analogWrite(ena, 0);
digitalWrite(in1, LOW);
digitalWrite(in2, LOW);
digitalWrite(motorPin1, LOW);
digitalWrite(motorPin2, LOW);
digitalWrite(motorPin3, LOW);
digitalWrite(motorPin4, LOW);
}

void xrange() {
const int range = vl.readRange();
Serial.print(" ");  
Serial.print(range);
}

void motor2() {
for (int m = 0; m < 45; m++) {
Backward2();
xrange();
}
Forward2();
}

void scan() {
for (int s = 0; s < 35; s++) {
motor2();
Serial.print(" ");  
Serial.println();
motor1();
}
motor2();
Serial.println();
motor1null();
}

void Forward() {
analogWrite(ena, 255);
digitalWrite(in1, LOW);
digitalWrite(in2, HIGH);
}

void Backward() {
analogWrite(ena, 255);
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
}

void Backward2() {
for (int i = 0; i < 45; i++) {
stepper.step(stepsPerRevolution / 8);
delay(5);
}}
    
void Forward2() {
for (int f = 0; f < 45; f++) {
for (int i = 0; i < 45; i++) {
stepper.step(-stepsPerRevolution / 8);
delay(5);
}}
} 

void setupScan() {
for (int m = 0; m < 45; m++) {
Backward2();
delay(5);
}
Forward2();
delay(5);
}

void loop() {
int reading = digitalRead(buttonPin);
if (reading != lastButtonState) {
lastDebounceTime = millis();
}
if ((millis() - lastDebounceTime) > debounceDelay) {
if (reading != buttonState) {
buttonState = reading;
if (buttonState == LOW) {
buttonPresses++;
scan();
buttonPresses = 0;
}}}
lastButtonState = reading;
}
