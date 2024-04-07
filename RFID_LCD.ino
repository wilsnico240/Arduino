#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
#include <SPI.h>
#include <MFRC522.h>
#define RST_PIN 9
#define SS_PIN 10 
#define IRQ_PIN 2
MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
volatile bool bNewInt = false;
byte regVal = 0x7F;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(F("Setup"));
  delay(1000);
  lcd.clear();
  lcd.noBacklight();
  delay(250);
  lcd.backlight();
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.print(F("Ver:0x"));
  lcd.setCursor(0, 0);
  lcd.print(F("Ver:0x"));
  byte readReg = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);
  Serial.println(readReg, HEX);
  lcd.setCursor(0, 1);
  lcd.print(readReg, HEX);
  delay(3000);
  lcd.clear();
  pinMode(IRQ_PIN, INPUT_PULLUP); 
  regVal = 0xA0;
  mfrc522.PCD_WriteRegister(mfrc522.ComIEnReg, regVal);
  bNewInt = false;
  attachInterrupt(digitalPinToInterrupt(IRQ_PIN), readCard, FALLING);  
  do {
    ;
  } while (!bNewInt);
  bNewInt = false;
  Serial.println(F("End setup"));
  lcd.setCursor(0, 0);
  lcd.print(F("End setup"));
  delay(1000);
  lcd.clear();
}

void loop() {
  if (bNewInt) { 
    Serial.print(F("Interrupt. "));
    lcd.clear();
    mfrc522.PICC_ReadCardSerial();
    Serial.print(F("Card UID:"));
    lcd.setCursor(0, 0);
    lcd.print(F("Card UID:"));
    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
    Serial.println();    
    clearInt(mfrc522);
    mfrc522.PICC_HaltA();
    bNewInt = false;
  }  
  activateRec(mfrc522);
  delay(100);
}
void readCard() {
  bNewInt = true;
}
void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
    lcd.setCursor(i * 3, 1);
    if (buffer[i] < 0x10) {
      lcd.print(F(" 0"));
    } else {
      lcd.print(F(" "));
    }
    lcd.print(buffer[i], HEX);
  }
}
void activateRec(MFRC522 mfrc522) {
  mfrc522.PCD_WriteRegister(mfrc522.FIFODataReg, mfrc522.PICC_CMD_REQA);
  mfrc522.PCD_WriteRegister(mfrc522.CommandReg, mfrc522.PCD_Transceive);
  mfrc522.PCD_WriteRegister(mfrc522.BitFramingReg, 0x87);
}
void clearInt(MFRC522 mfrc522) {
  mfrc522.PCD_WriteRegister(mfrc522.ComIrqReg, 0x7F);
}
