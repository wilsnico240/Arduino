#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#define RELAY1 5
#define RELAY2 6
#define ON  LOW
#define OFF HIGH

unsigned long startTime;
unsigned long currentTime;

void setup() {
  Serial.begin(9600);
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  digitalWrite(RELAY1, OFF);
  digitalWrite(RELAY2, OFF);
  dht.begin();
  startTime = millis();
}

void loop() {
  currentTime = millis();
  int temperature = dht.readTemperature();
  int humidity = dht.readHumidity();
  if (currentTime - startTime >= 300000) {
    startTime = currentTime;
    if (temperature >= 30) {
      digitalWrite(RELAY1, ON);
      Serial.println("Temperatuur is te hoog!");
    }
    else if (temperature <= 30) {
      digitalWrite(RELAY1, OFF);
      Serial.println("Temperatuur is in orde.");
    }
    if (humidity <= 40) {
      digitalWrite(RELAY2, ON);
      Serial.println("Luchtvochtigheid is te laag!");
      delay(180000);
      digitalWrite(RELAY2, OFF);
      Serial.println("Luchtvochtigheid is in orde.");
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
  Serial.println(" ");
}
