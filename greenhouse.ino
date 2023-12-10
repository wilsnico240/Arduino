// lcd: SCL=A5 SDA=A4
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 0
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

const int sensorPin = A3;
const int LDR = A2;
#define FAN1 1
#define FAN2 2
#define FAN3 3
#define FAN4 4
#define MIST 5
#define PUMP1 6
#define LED1 7
#define LED2 8
#define LED3 9
#define LED4 10
#define LED5 11
#define SWAVE 12
#define HEAT 13
#define ON  LOW
#define OFF HIGH

void(* resetFunc) (void) = 0;
unsigned long startTime;
unsigned long startTime2;
unsigned long startTime3;
unsigned long startTime4;
unsigned long startTime5;
unsigned long startTime6;
unsigned long currentTime;
unsigned long currentTime2;
unsigned long currentTime3;
unsigned long currentTime4;
unsigned long currentTime5;
unsigned long currentTime6;
byte speed = 40;
LiquidCrystal_I2C lcd(0x27, 20, 4);
const int wetThreshold = 300;
const int dryThreshold = 750;
int sensorValue = 0;
int percentage = 0;
const int minThreshold = 1050;
const int maxThreshold = 0;
int LDRValue = 0; 
int Lum = 0;

void setup() {
   lcd.init(); 
   lcd.backlight();
   Serial.begin(9600);
   pinMode(FAN1, OUTPUT);
   pinMode(FAN2, OUTPUT);
   pinMode(FAN3, OUTPUT);
   pinMode(FAN4, OUTPUT);
   pinMode(MIST, OUTPUT);
   pinMode(PUMP1, OUTPUT);
   pinMode(LED1, OUTPUT);
   pinMode(LED2, OUTPUT);
   pinMode(LED3, OUTPUT);
   pinMode(LED4, OUTPUT);
   pinMode(LED5, OUTPUT);
   pinMode(SWAVE, OUTPUT);
   pinMode(HEAT, OUTPUT);
   digitalWrite(FAN1, OFF);
   digitalWrite(FAN2, OFF);
   digitalWrite(FAN3, OFF);
   digitalWrite(FAN4, OFF);
   digitalWrite(MIST, OFF);
   digitalWrite(PUMP1, OFF);
   digitalWrite(LED1, ON);
   digitalWrite(LED2, ON);
   digitalWrite(LED3, ON);
   digitalWrite(LED4, ON);
   digitalWrite(LED5, ON);
   digitalWrite(SWAVE, OFF);
   digitalWrite(HEAT, OFF);
   dht.begin();
   startTime = millis();
   startTime2 = millis();
   startTime3 = millis();
   startTime4 = millis();
   startTime5 = millis();
   startTime6 = millis();
}
      
void loop() {
   currentTime = millis();
   currentTime2 = millis();
   currentTime3 = millis();
   currentTime4 = millis();
   currentTime5 = millis();
   currentTime6 = millis();
   int temperature = dht.readTemperature();
   int humidity = dht.readHumidity();
   sensorValue = analogRead(sensorPin);
   percentage = map(sensorValue, wetThreshold, dryThreshold, 100, 0);
   LDRValue = analogRead(LDR); 
   Lum = map(LDRValue, minThreshold, maxThreshold, 0, 1050);
analogWrite(FAN2, speed);
   analogWrite(FAN3, speed);
   analogWrite(FAN4, speed);
   if (currentTime2 - startTime2 >= 64800000) {
   startTime2 = currentTime2;
      digitalWrite(LED1, OFF);
      digitalWrite(LED2, OFF);
      digitalWrite(LED3, OFF);
      digitalWrite(LED4, OFF);
      digitalWrite(LED5, OFF);
      digitalWrite(SWAVE, ON);
      }
   if (currentTime3 - startTime3 >= 86400000) {
    startTime3 = currentTime3;
    resetFunc();
}
   if (currentTime4 - startTime4 >= 18000000) {
    startTime4 = currentTime4;
   if (humidity < 40) {
  lcd.setCursor(0, 0);
  lcd.print("H. air Low          ");
  lcd.setCursor(0, 1);
  lcd.print("propellers OFF      ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");
      digitalWrite(FAN2, OFF);
      digitalWrite(FAN3, OFF);
      digitalWrite(FAN4, OFF);
      delay(5000);
  lcd.setCursor(0, 2);
  lcd.print("Starting fog        ");
      digitalWrite(MIST, ON);
      delay(5000);
  lcd.setCursor(0, 2);
  lcd.print("Fog OFF             ");
     digitalWrite(MIST, OFF);
      delay(5000);
  lcd.setCursor(0, 1);
  lcd.print("Starting propellers ");
      analogWrite(FAN3, speed);
      delay(5000);
      analogWrite(FAN2, speed);
      analogWrite(FAN4, speed);
    }
    }
    if (currentTime5 - startTime5 >= 36000000) {
    startTime5 = currentTime5;
    if (percentage < 20)
  lcd.setCursor(0, 0);
  lcd.print("H. soil too low     ");
  lcd.setCursor(0, 1);
  lcd.print("Water pump ON       ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");
     digitalWrite(PUMP1, ON);
     delay(118000);
  lcd.setCursor(0, 1);
  lcd.print("Water pump OFF      ");
      delay(2000);
      digitalWrite(PUMP1, OFF);
      }
    if (currentTime - startTime >= 900000) {
    startTime = currentTime;
     if (temperature <= 20) {
  lcd.setCursor(0, 0);
  lcd.print("Temp.too low        ");
  lcd.setCursor(0, 1);
  lcd.print("Heating ON          ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");
      digitalWrite(HEAT, ON);
      delay(180000);
  lcd.setCursor(0, 2);
  lcd.print("Fan ON              ");
      digitalWrite(FAN1, ON);
      delay(540000);
  lcd.setCursor(0, 1);
  lcd.print("Heating  OFF        ");
      digitalWrite(HEAT, OFF);
      delay(58000);
  lcd.setCursor(0, 2);
  lcd.print("Fan OFF             ");
     delay(2000);
     digitalWrite(FAN1, OFF);
     }
  }
    if (currentTime6 - startTime6 >= 900000) {
    startTime = currentTime;
    if (temperature >= 30) {
  lcd.setCursor(0, 0);
  lcd.print("Temp.too high       ");
  lcd.setCursor(0, 1);
  lcd.print("Fan ON              ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");
      digitalWrite(FAN1, ON);
      delay(778000);
  lcd.setCursor(0, 1);
  lcd.print("Fan OFF             ");
      delay(2000);
      digitalWrite(FAN1, OFF);
     }
  }
  lcd.setCursor(0, 0);
  lcd.print("                    ");
  lcd.setCursor(0, 1);
  lcd.print("   Auto-Grow-Box    ");
  lcd.setCursor(0, 2);
  lcd.print("   -------------    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");
  delay(5000);
  lcd.setCursor(0, 0);
  lcd.print("Temperature:        ");
  lcd.setCursor(0, 1);
  lcd.print(temperature);
  lcd.print(" C                  ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");
  delay(2000);
  lcd.setCursor(0, 0);
  lcd.print("Humidity:           ");
  lcd.setCursor(0, 1);
  lcd.print(humidity);
  lcd.print(" %                  ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");
      delay(2000);
  lcd.setCursor(0, 0);
  lcd.print("Humidity soil:      ");
  lcd.setCursor(0, 1);
  lcd.print(percentage);
  lcd.print(" %                  ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");
      delay(2000);
  lcd.setCursor(0, 0);
  lcd.print("LDR power:          ");
  lcd.setCursor(0, 1);
  lcd.print(Lum);
  lcd.print("                    ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");
      delay(2000);
lcd.setCursor(0, 0);
  lcd.print("LED 1 :             ");
  if (digitalRead(LED1) == ON) {
  lcd.setCursor(0, 1);
  lcd.print("ON                  ");
  }
  else {
  lcd.setCursor(0, 1);
  lcd.print("OFF                 ");
  }
  lcd.setCursor(0, 2);
  lcd.print("LED 2 :             ");
  if (digitalRead(LED2) == ON) {
  lcd.setCursor(0, 3);
  lcd.print("ON                  ");
  }
  else {
  lcd.setCursor(0, 3);
  lcd.print("OFF                 ");
  }
        delay(2000);
  lcd.setCursor(0, 0);
  lcd.print("LED 3 :             ");
  if (digitalRead(LED3) == ON) {
  lcd.setCursor(0, 1);
  lcd.print("ON                  ");
  }
  else {
  lcd.setCursor(0, 3);
  lcd.print("OFF                 ");
  }
  lcd.setCursor(0, 2);
  lcd.print("LED 4 :             ");
  if (digitalRead(LED4) == ON) {
  lcd.setCursor(0, 3);
  lcd.print("ON                  ");
  }
  else {
  lcd.setCursor(0, 3);
  lcd.print("OFF                 ");
  }
      delay(2000);
  lcd.setCursor(0, 0);
  lcd.print("LED 5 :             ");
  if (digitalRead(LED5) == ON) {
  lcd.setCursor(0, 1);
  lcd.print("ON                  ");
  }
  else {
  lcd.setCursor(0, 1);
  lcd.print("OFF                 ");
  }
  lcd.setCursor(0, 2);
  lcd.print("Shumann Wave:       ");
  if (digitalRead(SWAVE) == ON) {
  lcd.setCursor(0, 3);
  lcd.print("ON                  ");
  }
  else {
  lcd.setCursor(0, 3);
  lcd.print("OFF                 ");
  }
      delay(2000);
}
