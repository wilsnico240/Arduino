#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#define FAN1 5
#define FAN2 7
#define FAN3 8
#define FAN4 9
#define MIST 6
#define PUMP1 11
#define LED1 2
#define LED2 3
#define ON  LOW
#define OFF HIGH

void(* resetFunc) (void) = 0;
unsigned long startTime;
unsigned long startTime2;
unsigned long startTime3;
unsigned long currentTime;
unsigned long currentTime2;
unsigned long currentTime3;
byte speed = 80;

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
   digitalWrite(FAN1, OFF);
   analogWrite(FAN2, speed);
   analogWrite(FAN3, speed);
   analogWrite(FAN4, speed);
   digitalWrite(MIST, OFF);
   digitalWrite(PUMP1, OFF);
   digitalWrite(LED1, ON);
   digitalWrite(LED2, ON);
   dht.begin();
   startTime = millis();
   startTime2 = millis();
   startTime3 = millis();
}

void loop() {
   currentTime = millis();
   currentTime2 = millis();
   currentTime3 = millis();
   int temperature = dht.readTemperature();
   int humidity = dht.readHumidity();
   
    if (currentTime2 - startTime2 >= 64800000) {
    startTime2 = currentTime2;
      digitalWrite(LED1, OFF);
      digitalWrite(LED2, OFF);
      }
    if (currentTime3 - startTime3 >= 86400000) {
    startTime3 = currentTime3;
    resetFunc();
}
    if (currentTime - startTime >= 300000) {
    startTime = currentTime;
    if (temperature >= 22) {
      digitalWrite(FAN1, ON);
    }
    else if (temperature <= 22) {
      digitalWrite(FAN1, OFF);
    }
    if (humidity <= 65) {
      digitalWrite(FAN2, OFF);
      digitalWrite(FAN3, OFF);
      digitalWrite(FAN4, OFF);
      delay(5000);
      digitalWrite(MIST, ON);
      delay(20000);
      digitalWrite(MIST, OFF);
      delay(5000);
      analogWrite(FAN3, speed);
      delay(5000);
      analogWrite(FAN2, speed);
      analogWrite(FAN4, speed);
    }
  }
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  Serial.print("LED 1 ");
  if (digitalRead(LED1) == ON) {
    Serial.println("on.");
  }
  else {
    Serial.println("off.");
  }

  Serial.print("LED 2 ");
  if (digitalRead(LED2) == ON) {
    Serial.println("on.");
  }
  else {
    Serial.println("off.");
  }
  
  Serial.println(" ");
}
