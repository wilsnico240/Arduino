#include <SPI.h>
#include <SoftwareSerial.h>
SoftwareSerial RFID2(6, 8);
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#define SS_PIN 10
#define RST_PIN 9
#define LED_RED 4
#define LED_GREEN 5
MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);
int data1 = 0;
int ok=-1;
int tag1[14]={2,52,56,48,48,67,66,66,52,68,68,69,65,3};
int tag2[14]={2,52,56,48,48,67,54,65,50,55,55,53,66,3};
int newtag[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int okdelay = 2000; 
int notokdelay = 2000;

bool bNewInt = false;

void setup() {
    Serial.flush();
    Serial.begin(9600);
    RFID2.begin(9600);
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
    lcd.print(F("Version:     "));
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

boolean comparetag(int aa[14], int bb[14])
{
  boolean ff=false;
  int fg=0;
  for (int cc=0; cc<14; cc++)
  {
    if (aa[cc]==bb[cc])
    {
      fg++;
    }
  }
  if (fg==14)
  {
    ff=true;
  }
  return ff;
}

void checkmytags()
{
  ok=0;
  if (comparetag(newtag,tag1)==true)
  {
    ok++;
    
  }
  if (comparetag(newtag,tag2)==true)
  {
    ok++;
  }
}

void readTag() 
{
  ok=-1;
  if (RFID2.available() > 0)
  {
    delay(100);
    for (int z=0; z<14; z++) 
    {
      data1=RFID2.read();
      newtag[z]=data1;
    }
    RFID2.flush();
    checkmytags(); 
  }
  if (ok>0==true)
  {
    digitalWrite(LED_GREEN, HIGH);
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print(F("ID:      "));
    lcd.setCursor(0, 1);
    lcd.print(F("----------------"));
    delay(okdelay);
    digitalWrite(LED_GREEN, LOW);
    lcd.clear();
    delay(500);
    lcd.noBacklight();
    ok=-1;
  } 
  else if (ok==0)
  {
    digitalWrite(LED_RED, HIGH);
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print(F("ID:      "));
    lcd.setCursor(0, 1);
    lcd.print(F("----------------"));
    delay(notokdelay);
    digitalWrite(LED_RED, LOW);
    lcd.clear();
    delay(500);
    lcd.noBacklight();
    ok=-1;
  }
}

void loop() {
      readTag();
      if(RFID2.available()>0){
           Serial.print(F("Card UID: "));
          delay(1000);
           while(RFID2.available()>0){
           int i=RFID2.read();
           Serial.print(i,DEC);
           Serial.print(",");
          }
          Serial.println();
          delay(2000);
}
      if (bNewInt) {
          lcd.backlight();
          mfrc522.PICC_ReadCardSerial();
          Serial.print(F("Card UID: "));
          lcd.setCursor(0, 0);
          lcd.print(F("ID:      "));
          lcd.setCursor(0, 1);
          lcd.print(F("----------------"));
          Serial.println();
          mfrc522.PICC_HaltA();
          if (memcmp(mfrc522.uid.uidByte, (byte *)"\x33\x90\x7D\x18", 4) == 0 ||
            memcmp(mfrc522.uid.uidByte, (byte *)"\x23\xEC\xE2\xA6", 4) == 0 ||
            memcmp(mfrc522.uid.uidByte, (byte *)"\x83\x0A\x76\x18", 4) == 0 ||
            memcmp(mfrc522.uid.uidByte, (byte *)"\x73\x9B\xEF\xA5", 4) == 0) {
            digitalWrite(LED_GREEN, HIGH);
            delay(2000);
            digitalWrite(LED_GREEN, LOW);
          }
          else {
            digitalWrite(LED_RED, HIGH);
            delay(2000);
            digitalWrite(LED_RED, LOW);
          }
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
