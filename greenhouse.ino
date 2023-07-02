
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#define RELAY1 5
#define RELAY2 6
#define RELAY3 2
#define RELAY4 3
#define ON  LOW
#define OFF HIGH

void(* resetFunc) (void) = 0;
unsigned long startTime;
unsigned long startTime2;
unsigned long startTime3;
unsigned long currentTime;
unsigned long currentTime2;
unsigned long currentTime3;
void setup() {
   Serial.begin(9600);
   pinMode(RELAY1, OUTPUT);
   pinMode(RELAY2, OUTPUT);
   pinMode(RELAY3, OUTPUT);
   pinMode(RELAY4, OUTPUT);
   digitalWrite(RELAY1, OFF);
   digitalWrite(RELAY2, OFF);
   digitalWrite(RELAY3, ON);
   digitalWrite(RELAY4, ON);
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
      digitalWrite(RELAY3, OFF);
      digitalWrite(RELAY4, OFF);
      }
    if (currentTime3 - startTime3 >= 86400000) {
    startTime3 = currentTime3;
    resetFunc();
}
    if (currentTime - startTime >= 300000) {
    startTime = currentTime;
    if (temperature >= 28) {
      digitalWrite(RELAY1, ON);
    }
    else if (temperature <= 28) {
      digitalWrite(RELAY1, OFF);
    }
    if (humidity <= 50) {
      digitalWrite(RELAY2, ON);
      delay(30000);
      digitalWrite(RELAY2, OFF);
    }
  }
  Serial.print("Temperatuur: ");
  Serial.print(temperature);
  Serial.println("C");
  Serial.print("Luchtvochtigheid: ");
  Serial.print(humidity);
  Serial.println("%");
  Serial.print("Relais 1 staat ");
  if (digitalRead(RELAY1) == ON) {
    Serial.println("aan.");
  }
  else {
    Serial.println("uit.");
  }
  Serial.print("Relais 2 staat ");
  if (digitalRead(RELAY2) == ON) {
    Serial.println("aan.");
  }
  else {
    Serial.println("uit.");
  }
  Serial.print("Relais 3 staat ");
  if (digitalRead(RELAY3) == ON) {
    Serial.println("aan.");
  }
  else {
    Serial.println("uit.");
  }

  Serial.print("Relais 4 staat ");
  if (digitalRead(RELAY4) == ON) {
    Serial.println("aan.");
  }
  else {
    Serial.println("uit.");
  }

  Serial.println(" ");
}
