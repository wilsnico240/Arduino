#include <LiquidCrystal.h>
#include <Wire.h>
#include <RTClib.h>
DateTime now;
RTC_DS3231 rtc;
#include <BH1750.h>
BH1750 lightMeter;
#include <Adafruit_BMP085.h>
Adafruit_BMP085 bmp;
#include <SimpleDHT.h>
int pinDHT22 = 2;
SimpleDHT22 dht22(pinDHT22);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
#define btnRIGHT 0
#define btnUP 1
#define btnDOWN 2
#define btnLEFT 3
#define btnSELECT 4
#define btnNONE 5
unsigned long lastButtonPressTime = 0;
unsigned long lastAnalogReadTime = 0;
unsigned long buttonPressInterval = 250;
unsigned long analogReadInterval = 1000;
bool backlightOn = true;
float temperature = 0;
float humidity = 0;
float lumiere = 0;
float pressure = 0;
int lcd_key = 0;
int adc_key_in = 0;
int menuIndex = 0;
int read_LCD_buttons() {
   adc_key_in = analogRead(0);
   if (adc_key_in < 50) return btnRIGHT;
   if (adc_key_in < 195) return btnUP;
   if (adc_key_in < 380) return btnDOWN;
   if (adc_key_in < 555) return btnLEFT;
   if (adc_key_in < 790) return btnSELECT;
   return btnNONE;
}

void toggleBacklight() {
   backlightOn = !backlightOn;
   if (backlightOn) {
      lcd.display();
      digitalWrite(10, HIGH);
   } else {
      lcd.noDisplay();
      digitalWrite(10, LOW);
   }
}

void updateTemperatureAndHumidity() {
int err = SimpleDHTErrSuccess;
if((err=dht22.read2(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess){
  delay(200);
     return;
    }
    }

void displayMenu() {
    switch(menuIndex) {
      case 0:
        lcd.setCursor(0, 0);
        now = rtc.now();
        lcd.setCursor(0,0);
        lcd.print("Date:");
        lcd.print(now.day());
        lcd.print('/');
        lcd.print(now.month());
        lcd.print('/');
        lcd.print(now.year());
        lcd.setCursor(0, 1);
        now = rtc.now();
        lcd.print("Temps:");
        lcd.print(now.hour());
        lcd.print(':');
        lcd.print(now.minute());
        lcd.print(':');
        lcd.print(now.second());
        lcd.print("    ");
        break;
      case 1:
        lcd.setCursor(0, 0);
        lcd.print("Temperature:    ");
        lcd.setCursor(0, 1);
        lcd.print(temperature);
        lcd.print(" C.       ");
        break;
      case 2:
        lcd.setCursor(0, 0);
        lcd.print("Humidite:       ");
        lcd.setCursor(0, 1);
        lcd.print(humidity);
        lcd.print("%         ");
        break;
      case 3:
        lcd.setCursor(0, 0);
        lcd.print("Lux:            ");
        lcd.setCursor(0, 1);
        if (millis() - lastAnalogReadTime > analogReadInterval) {
          lumiere = lightMeter.readLightLevel();
          lastAnalogReadTime = millis();
        }
        lcd.print(lumiere);
        lcd.print(" Lx.      ");
        break;
      case 4:
        lcd.setCursor(0, 0);
        lcd.print("Pression:       ");
        lcd.setCursor(0, 1);
        if (millis() - lastAnalogReadTime > analogReadInterval) {
          pressure = bmp.readPressure();
          lastAnalogReadTime = millis();
        }
        lcd.print(pressure);
        lcd.print(" Pa.      ");
        break;
    }
}

void setup() {
   Serial.begin(9600);
   pinMode(10, OUTPUT);
   digitalWrite(10, HIGH);
   lcd.begin(16, 2);
   lcd.display();
   Wire.begin();
   lightMeter.begin();
   bmp.begin();
   rtc.begin();
  }  
void loop() {
    if (millis() - lastAnalogReadTime > analogReadInterval) {
        updateTemperatureAndHumidity();
        lastAnalogReadTime = millis();
    }
      lcd_key = read_LCD_buttons();
   if(lcd_key == btnRIGHT) {
     if (millis() - lastButtonPressTime > buttonPressInterval) {
       menuIndex++;
       if (menuIndex > 4) {
         menuIndex = 0;
       }
       lastButtonPressTime = millis();
     }
   }
   if(lcd_key == btnLEFT) {
     if (millis() - lastButtonPressTime > buttonPressInterval) {
       menuIndex--;
       if (menuIndex < 0) {
         menuIndex = 4;
       }
       lastButtonPressTime = millis();
     }
   }
   if(lcd_key == btnSELECT) {
     if (millis() - lastButtonPressTime > buttonPressInterval) {
     toggleBacklight();
     }
     lastButtonPressTime = millis();
   }
   displayMenu();
}
