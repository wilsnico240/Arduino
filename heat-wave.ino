void(* resetFunc) (void) = 0;
#include <Servo.h>
Servo servo1;
Servo servo2;
#include <Keypad.h>
#define NOTE_C4 262
#define NOTE_C5 523
#define NOTE_C6 1047
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}};
byte rowPins[ROWS] = {4, 5, 6, 7};
byte colPins[COLS] = {8, 9, 10, 11};
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins,
ROWS, COLS);
Keypad customKeypad2 = Keypad( makeKeymap(hexaKeys), rowPins, colPins,
ROWS, COLS);
String inputCode = "";
String inputCode2 = "";
const int SPEAKER = 12;
int relayPin = 3;
int fan1Pin = A1;
int fan2Pin = A2;
int fan3Pin = A3;
int x_key = A4;
int y_key = A5;
int x_pos;
int y_pos;
int servo1_pin = 2;
int servo2_pin = 13;
int initial_position = 90;
int initial_position1 = 90;
bool statew = false;
bool statef3 = false;
bool statef2 = false;
bool statef1 = false;

void setup(){
Serial.begin(9600);
pinMode (relayPin, OUTPUT);
pinMode (fan1Pin, OUTPUT);
pinMode (fan2Pin, OUTPUT);
pinMode (fan3Pin, OUTPUT);
pinMode(SPEAKER,OUTPUT);
servo1.attach (servo1_pin ) ;
servo2.attach (servo2_pin ) ;
servo1.write (initial_position);
servo2.write (initial_position1);
pinMode (x_key, INPUT) ;
pinMode (y_key, INPUT) ;
digitalWrite(SPEAKER,LOW);
digitalWrite(relayPin, LOW);
digitalWrite(fan1Pin, HIGH);
digitalWrite(fan2Pin, HIGH);
digitalWrite(fan3Pin, HIGH);
}

void servo(){
x_pos = analogRead (x_key) ;
y_pos = analogRead (y_key) ;
if (x_pos < 300){
if (initial_position < 20) { } else{ initial_position = initial_position
- 5; servo1.write ( initial_position ) ; delay (50) ; } } if (x_pos > 700){
if (initial_position > 160)
{
}
else{
initial_position = initial_position + 5;
servo1.write ( initial_position ) ;
delay (50) ;
}
}
if (y_pos < 300){
if (initial_position1 < 20) { } else{ initial_position1 =
initial_position1 - 5; servo2.write ( initial_position1 ) ; delay (50) ;
} } if (y_pos > 700){
if (initial_position1 > 160)
{
}
else{
initial_position1 = initial_position1 + 5;
servo2.write ( initial_position1 ) ;
delay (50) ;
}
}
}

void motor1(){
if(statef1){
digitalWrite(fan1Pin, LOW);
statef1 = false;
}
else {
digitalWrite(fan1Pin, HIGH);
statef1 = true;
}}

void motor2(){
if(statef2){
digitalWrite(fan2Pin, LOW);
statef2 = false;
}
else {
digitalWrite(fan2Pin, HIGH);
statef2 = true;
}}

void motor3(){
if(statef3){
digitalWrite(fan3Pin, LOW);
statef3 = false;
}
else {
digitalWrite(fan3Pin, HIGH);
statef3 = true;
}}

void pump(){
   if(statew){
digitalWrite(relayPin, LOW);
statew = false;
}
else {
digitalWrite(relayPin, HIGH);
statew = true;
}}

void keycode2(){
servo();
char customKey2 = customKeypad.getKey();
if (customKey2){
if (customKey2 != '#'){
inputCode2 += customKey2;
}
else {
if (inputCode2 == "2812") {
resetFunc();
}
inputCode2 = "";
}}
switch (customKey2) {
case '0':
Serial.println('0');
tone(SPEAKER,NOTE_C4, 350);
break;
case '1':
Serial.println('1');
tone(SPEAKER,NOTE_C4, 350);
break;
case '2':
Serial.println('2');
tone(SPEAKER,NOTE_C4, 350);
break;
case '3':
Serial.println('3');
tone(SPEAKER,NOTE_C4, 350);
break;
case '4':
Serial.println('4');
tone(SPEAKER,NOTE_C4, 350);
break;
case '5':
Serial.println('5');
tone(SPEAKER,NOTE_C4, 350);
break;
case '6':
Serial.println('6');
tone(SPEAKER,NOTE_C4, 350);
break;
case '7':
Serial.println('7');
tone(SPEAKER,NOTE_C4, 350);
break;
case '8':
Serial.println('8');
tone(SPEAKER,NOTE_C4, 350);
break;
case '9':
Serial.println('9');
tone(SPEAKER,NOTE_C4, 350);
break;
case 'A':
Serial.println('A');
motor1();
break;
case 'B':
Serial.println('B');
motor2();
break;
case 'C':
Serial.println('C');
motor3();
break;
case 'D':
Serial.println('D');
pump();
break;
case '*':
Serial.println('*');
tone(SPEAKER,NOTE_C5, 350);
break;
case '#':
Serial.println('#');
tone(SPEAKER,NOTE_C6, 350);
break;
}
keycode2();
}

void keycode(){
char customKey = customKeypad.getKey();
if (customKey){
if (customKey != '#'){
inputCode += customKey;
}
else {
if (inputCode == "2812") {
keycode2();
}
inputCode = "";
}}
switch (customKey) {
case '0':
Serial.println('0');
tone(SPEAKER,NOTE_C4, 350);
break;
case '1':
Serial.println('1');
tone(SPEAKER,NOTE_C4, 350);
break;
case '2':
Serial.println('2');
tone(SPEAKER,NOTE_C4, 350);
break;
case '3':
Serial.println('3');
tone(SPEAKER,NOTE_C4, 350);
break;
case '4':
Serial.println('4');
tone(SPEAKER,NOTE_C4, 350);
break;
case '5':
Serial.println('5');
tone(SPEAKER,NOTE_C4, 350);
break;
case '6':
Serial.println('6');
tone(SPEAKER,NOTE_C4, 350);
break;
case '7':
Serial.println('7');
tone(SPEAKER,NOTE_C4, 350);
break;
case '8':
Serial.println('8');
tone(SPEAKER,NOTE_C4, 350);
break;
case '9':
Serial.println('9');
tone(SPEAKER,NOTE_C4, 350);
break;
case 'A':
Serial.println('A');
break;
case 'B':
Serial.println('B');
break;
case 'C':
Serial.println('C');
break;
case 'D':
Serial.println('D');
break;
case '*':
Serial.println('*');
tone(SPEAKER,NOTE_C5, 350);
break;
case '#':
Serial.println('#');
tone(SPEAKER,NOTE_C6, 350);
break;
   }
}

void loop(){
keycode();
}
