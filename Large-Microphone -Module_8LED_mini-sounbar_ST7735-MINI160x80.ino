#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#define TFT_RST -1
#define TFT_CS 12
#define TFT_DC 8
#define TFT_MOSI 11
#define TFT_SCLK 13
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
int sensorPin = A0;
int sensorValue = 0;
int percentage;
int ledPins[] = {2, 3, 4, 5, 6, 7, 9, 10};
int xPos = 0;

void setup(){
    Serial.begin(9600);
    tft.initR(INITR_MINI160x80);
    tft.setRotation(3);
    uint16_t time = millis();
    tft.fillScreen(ST77XX_BLACK);
    time = millis() - time;
    testfastlines(ST77XX_YELLOW, ST77XX_BLUE);
    tft.fillScreen(ST77XX_BLACK);
    for(int i=0; i<8; i++){
        pinMode(ledPins[i], OUTPUT);
        digitalWrite(ledPins[i], LOW);
    }
}

void testfastlines(uint16_t color1, uint16_t color2) {
    tft.fillScreen(ST77XX_BLACK);
    for (int16_t y=0; y < tft.height(); y+=5) {
        tft.drawFastHLine(0, y, tft.width(), color1);
    }
    for (int16_t x=0; x < tft.width(); x+=5) {
        tft.drawFastVLine(x, 0, tft.height(), color2);
    }
}

void bar(uint16_t color, int height) {
    static int prevXPos = 0;
    if (xPos == 0 && prevXPos == tft.width() - 1) {
        tft.fillScreen(ST77XX_BLACK);
    }
    tft.drawLine(prevXPos, 0, prevXPos+1, tft.height(), ST77XX_BLACK);
    tft.drawLine(xPos, tft.height() - height, xPos, tft.height(), color);
    prevXPos = xPos;
    xPos++;
    if(xPos >= tft.width()) {
        xPos = 0;
    }
}

void led() {
  for(int i=0; i<8; i++){
    if(percentage >= ((i+1)*12.5)){
      digitalWrite(ledPins[i], HIGH);
    } else {
      digitalWrite(ledPins[i], LOW);
        }
  }
}

void loop(){
    sensorValue = analogRead(sensorPin);
    percentage = map(sensorValue, 229, 300, 0, tft.height());
    led();
    bar(ST77XX_YELLOW, percentage);
    }
