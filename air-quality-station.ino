#define BIZZER_PIN 4
#include "MQ135.h"
const int MQ135pin = A3;
MQ135 gasSensor = MQ135(MQ135pin);
#include "MQ7.h"
#define A_PIN A1
#define VOLTAGE 5
MQ7 mq7(A_PIN, VOLTAGE);
#include <Adafruit_BMP085.h>
#include <LiquidCrystal_I2C.h>
#define THERMISOR_PIN A3
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
#include <DHT.h>
#define DHTPIN A0
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085 bmp;
int Touch = 3;
const int green_led = 8;
const int orange_led = 9;
const int red_led = 10;
float Temperature;
float Humidity;
float PPM;
float GAS;
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
    Serial.begin(9600);
    bmp.begin();
    dht.begin();
    lcd.init();
    lcd.clear();
    pinMode(BIZZER_PIN, OUTPUT);
    pinMode (green_led, OUTPUT);
    pinMode (orange_led, OUTPUT);
    pinMode (red_led, OUTPUT);
    pinMode(Touch, INPUT);
    digitalWrite(green_led, LOW);
    digitalWrite(orange_led, LOW);
    digitalWrite(red_led, LOW);
    lcd.backlight();
    delay(1000);
    lcd.setCursor(0, 0);
    lcd.print("      Bonjour       ");
    lcd.setCursor(0, 1);
    lcd.print("                    ");
    lcd.setCursor(0, 2);
    lcd.print("                    ");
    lcd.setCursor(0, 3);
    lcd.print("                    ");
    delay(2000);
    lcd.setCursor(0, 1);
    lcd.print(" Le systeme demarre ");
    lcd.setCursor(0, 2);
    delay(2000);
    lcd.setCursor(0, 2);
    lcd.print("Preparation capteurs");
    delay(2000);
    lcd.setCursor(0, 3);
    lcd.print("Etalonnage capteurs!");
    mq7.calibrate();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("                    ");
    lcd.setCursor(0, 1);
    lcd.print("Le systeme est pret!");
    lcd.setCursor(0, 2);
    lcd.print("--------------------");
    lcd.setCursor(0, 3);
    lcd.print("                    ");
    delay(3000);
    lcd.clear();
    lcd.noBacklight();
}

void loop() {
    delay(250);
    GAS = gasSensor.getRZero();
    PPM = mq7.readPpm();
    Humidity = dht.readHumidity();
    Vo = analogRead(THERMISOR_PIN);
    R2 = R1 * (1023.0 / (float)Vo - 1.0);
    logR2 = log(R2);
    T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
    T = T - 276.25;
    lcd.setCursor(0, 0);
    lcd.print("Ppm:");
    lcd.print(GAS);
    lcd.print("%");
    lcd.print(" Co:");
    lcd.print(PPM);
    lcd.print("%   ");
    lcd.setCursor(0, 1);
    lcd.print("Temperature:");
    lcd.print(T);
    lcd.print("c   ");
    lcd.setCursor(0, 2);
    lcd.print("Humidite:");
    lcd.print(Humidity);
    lcd.print("%   ");
    lcd.setCursor(0, 3);
    lcd.print("Pression:");
    lcd.print(bmp.readPressure());
    lcd.print("pa   ");
    if ((GAS <= 18.00))
  {
    digitalWrite(green_led, HIGH);
    digitalWrite(orange_led, LOW);
    digitalWrite(red_led, LOW);
  }
    else if ((GAS > 18.00) && (GAS <= 18.50))
  {
    digitalWrite(green_led, HIGH);
    digitalWrite(orange_led, HIGH);
    digitalWrite(red_led, LOW);
  }
    else if ((GAS > 18.50) && (GAS <= 19.00))
  {
    digitalWrite(green_led, LOW);
    digitalWrite(orange_led, HIGH);
    digitalWrite(red_led, LOW);
  }
    else if ((GAS > 19.00) && (GAS <= 20.00))
  {
    digitalWrite(green_led, LOW);
    digitalWrite(orange_led, HIGH);
    digitalWrite(red_led, HIGH);
  }
    else if ((GAS > 20.00))
  {
    digitalWrite(green_led, LOW);
    digitalWrite(orange_led, LOW);
    digitalWrite(red_led, HIGH);
  }
    if ((PPM <= 20.00))
  {
    digitalWrite(BIZZER_PIN, LOW);
  }
    else if ((PPM > 20.00))
  {
    digitalWrite(BIZZER_PIN, HIGH);
  }
    if (digitalRead(Touch) == HIGH) {
    lcd.backlight();
    delay(10000);
        }
    else {
    lcd.noBacklight();
        }
        while(digitalRead(Touch) == HIGH) { }
        }

