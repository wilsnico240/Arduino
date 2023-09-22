#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#define SOIL A0
#define FAN1 5
#define FAN2 7
#define FAN3 8
#define FAN4 9
#define MIST 6
#define PUMP1 11
#define LED1 2
#define LED2 3
#define LED3 10
#define LED4 12
#define LED5 13
#define ON  LOW
#define OFF HIGH
#define THRESHOLD 300

void(* resetFunc) (void) = 0;
unsigned long startTime;
unsigned long startTime2;
unsigned long startTime3;
unsigned long startTime4;
unsigned long startTime5;
unsigned long currentTime;
unsigned long currentTime2;
unsigned long currentTime3;
unsigned long currentTime4;
unsigned long currentTime5;
byte speed = 40;

void setup() {
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
   dht.begin();
   startTime = millis();
   startTime2 = millis();
   startTime3 = millis();
   startTime4 = millis();
   startTime5 = millis();
}

void loop() {
   currentTime = millis();
   currentTime2 = millis();
   currentTime3 = millis();
   currentTime4 = millis();
   currentTime5 = millis();
   int temperature = dht.readTemperature();
   int humidity = dht.readHumidity();
   int value = analogRead(SOIL);
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
      }
    if (currentTime3 - startTime3 >= 86400000) {
    startTime3 = currentTime3;
    resetFunc();
}
    if (currentTime4 - startTime4 >= 18000000) {
    startTime4 = currentTime4;
    if (humidity < 65) {
      digitalWrite(FAN2, OFF);
      digitalWrite(FAN3, OFF);
      digitalWrite(FAN4, OFF);
      delay(5000);
      digitalWrite(MIST, ON);
      delay(5000);
      digitalWrite(MIST, OFF);
      delay(5000);
      analogWrite(FAN3, speed);
      delay(5000);
      analogWrite(FAN2, speed);
      analogWrite(FAN4, speed);
    }
    }
    if (currentTime5 - startTime5 >= 82800000) {
    startTime5 = currentTime5;
    if (value < THRESHOLD)
      digitalWrite(PUMP1, ON);
      delay(10000);
      digitalWrite(PUMP1, OFF);
      }
    if (currentTime - startTime >= 300000) {
    startTime = currentTime;
    if (temperature >= 22) {
      digitalWrite(FAN1, ON);
    }
    else if (temperature < 22) {
      digitalWrite(FAN1, OFF);
    }
  }
  Serial.print("Temperatuur: ");
  Serial.print(temperature);
  Serial.println("C");
  Serial.print("Luchtvochtigheid: ");
  Serial.print(humidity);
  Serial.println("%");
  Serial.print("Bodemvochtigheid: ");
  Serial.println(value);

  Serial.print("LED 1 staat ");
  if (digitalRead(LED1) == ON) {
    Serial.println("aan.");
  }
  else {
    Serial.println("uit.");
  }

  Serial.print("LED 2 staat ");
  if (digitalRead(LED2) == ON) {
    Serial.println("aan.");
  }
  else {
    Serial.println("uit.");
  }
  
  Serial.print("LED 3 staat ");
  if (digitalRead(LED3) == ON) {
    Serial.println("aan.");
  }
  else {
    Serial.println("uit.");
  }
  Serial.print("LED 4 staat ");
  if (digitalRead(LED4) == ON) {
    Serial.println("aan.");
  }
  else {
    Serial.println("uit.");
  }
  Serial.print("LED 5 staat ");
  if (digitalRead(LED5) == ON) {
    Serial.println("aan.");
  }
  else {
    Serial.println("uit.");
  }

  Serial.println(" ");
      delay(200);
}
