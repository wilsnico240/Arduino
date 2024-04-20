#include <SPI.h>
#include <SoftwareSerial.h>
SoftwareSerial RFID2(6, 8);
#include <LiquidCrystal_I2C.h>
#define LED_RED 4
#define LED_GREEN 5
#define LOCK 9
LiquidCrystal_I2C lcd(0x27, 16, 2);
int data1 = 0;
int ok=-1;
int tag1[14]={2,52,56,48,48,67,66,66,52,68,68,69,65,3};
int tag2[14]={2,52,56,48,48,67,54,65,50,55,55,53,66,3};
int newtag[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int okdelay = 3000; 
int notokdelay = 2000;

void setup() {
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
pinMode(LOCK, OUTPUT);
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
}}
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
lcd.backlight();
lcd.setCursor(0, 0);
lcd.print(F("Bonjour    "));
lcd.setCursor(0, 1);
lcd.print(F("Nico"));
ok++;
}
if (comparetag(newtag,tag2)==true)
{
lcd.backlight();
lcd.setCursor(0, 0);
lcd.print(F("Bonjour    "));
lcd.setCursor(0, 1);
lcd.print(F("Ben"));
ok++;
}}

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
delay(okdelay);
digitalWrite(LOCK, HIGH);
delay(2000);
digitalWrite(LOCK, LOW);
digitalWrite(LED_GREEN, LOW);
lcd.clear();
delay(2000);
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
}}

void loop() {
readTag();
if(RFID2.available()>0){
Serial.print(F("Card UID: "));
while(RFID2.available()>0){
int i=RFID2.read();
Serial.print(i,DEC);
Serial.print(",");
}
Serial.println();
delay(500);
}
}
