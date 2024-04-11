#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#define SS_PIN 10
#define RST_PIN 9
#define LED_RED 4
#define LED_GREEN 5
MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);

bool bNewInt = false;

void setup() {
    Serial.begin(9600);
  lcd.init();
  lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print(F("RFID Reader"));
  delay(3000);
  lcd.setCursor(0, 0);
  lcd.print(F("Setup        "));
  delay(2000);
    SPI.begin();
    mfrc522.PCD_Init();
  Serial.print(F("Ver:0x"));
  lcd.setCursor(0, 0);
  lcd.print(F("Version:      "));
  byte readReg = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);
  Serial.println(readReg, HEX);
  lcd.setCursor(0, 1);
  lcd.print(readReg, HEX);
  delay(3000);
  lcd.clear();
        delay(500);
  lcd.setCursor(0, 0);
  lcd.print(F("End setup"));
  delay(2000);
  lcd.clear();
  delay(500);
        lcd.noBacklight();
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    Serial.println(F("Ready to scan..."));
}

void loop() {
    if (bNewInt) {
        lcd.backlight();
        Serial.print(F("Interrupt. "));
        mfrc522.PICC_ReadCardSerial();
        Serial.print(F("Card UID: "));
        lcd.setCursor(0, 0);
        lcd.print(F("ID:      "));
        lcd.setCursor(0, 1);
        dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
        Serial.println();
        mfrc522.PICC_HaltA();
        if (memcmp(mfrc522.uid.uidByte, (byte *)"\x33\x90\x7D\x18", 4) == 0 || 
        memcmp(mfrc522.uid.uidByte, (byte *)"\x53\x5C\x76\xEE", 4) == 0 || 
        memcmp(mfrc522.uid.uidByte, (byte *)"\xA3\xD5\x68\x18", 4) == 0 || 
        memcmp(mfrc522.uid.uidByte, (byte *)"\x63\xBD\xE8\xA6", 4) == 0 || 
        memcmp(mfrc522.uid.uidByte, (byte *)"\x13\xB3\xE4\xA5", 4) == 0 || 
        memcmp(mfrc522.uid.uidByte, (byte *)"\x23\xEC\xE2\xA6", 4) == 0) {
        digitalWrite(LED_GREEN, HIGH);
       }
       else {
       digitalWrite(LED_RED, HIGH);
       }
        delay(2000);
        digitalWrite(LED_RED, LOW);
        digitalWrite(LED_GREEN, LOW);
        bNewInt = false;
        delay(1000);
        lcd.clear();
        delay(500);
        lcd.noBacklight();
    }
    activateRec(mfrc522);
    delay(100);
}

void activateRec(MFRC522 &mfrc522) {
    if (!mfrc522.PICC_IsNewCardPresent()) {
        return;
    }
    if (!mfrc522.PICC_ReadCardSerial()) {
        return;
    }
    bNewInt = true;
}

void dump_byte_array(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? "0" : "");
        Serial.print(buffer[i], HEX);
        lcd.print(buffer[i] < 0x10 ? " 0" : " ");
        lcd.print(buffer[i], HEX);
    }
}
