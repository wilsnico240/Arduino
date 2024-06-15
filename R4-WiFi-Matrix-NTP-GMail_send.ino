#include <WiFiS3.h>
#include <ESP_Mail_Client.h>
#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"
#include <NTPClient.h>
#include <WiFiUdp.h>
#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465
#define AUTHOR_EMAIL "*********@gmail.com"
#define AUTHOR_PASSWORD "************"
#define RECIPIENT_EMAIL "****************"
SMTPSession smtp;
char ssid[] = "**************";
char pass[] = "***************";
int status = WL_IDLE_STATUS;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "be.pool.ntp.org");
char* weekday[7] = { "Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi" };
ArduinoLEDMatrix matrix;
const uint32_t heart[] = {
0x3184a444,
0x44042081,
0x100a0040
};

uint8_t frame[8][12] = {
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

void leftEye(){
frame[1][3] = 1;
frame[1][4] = 1;
frame[2][3] = 1;
frame[2][4] = 1;
}

void wink(){
frame[1][3] = 0;
frame[1][4] = 0;
frame[2][3] = 1;
frame[2][4] = 1;
}

void wink2(){
frame[1][8] = 0;
frame[1][9] = 0;
frame[2][8] = 1;
frame[2][9] = 1;
}

void rightEye(){
frame[1][8] = 1;
frame[1][9] = 1;
frame[2][8] = 1;
frame[2][9] = 1;
}

void nose(){
frame[3][6] = 1;
frame[4][5] = 1;
frame[4][6] = 1;
frame[4][7] = 1;
}

void mouth(){
frame[5][3] = 1;
frame[5][9] = 1;
frame[6][3] = 1;
frame[6][4] = 1;
frame[6][5] = 1;
frame[6][6] = 1;
frame[6][7] = 1;
frame[6][8] = 1;
frame[6][9] = 1;
}

void mouth2(){
frame[5][3] = 0;
frame[5][9] = 0;
frame[6][3] = 1;
frame[6][4] = 1;
frame[6][5] = 1;
frame[6][6] = 1;
frame[6][7] = 1;
frame[6][8] = 1;
frame[6][9] = 1;
frame[7][6] = 0;
}

void mouth3(){
frame[5][3] = 0;
frame[5][9] = 0;
frame[6][3] = 1;
frame[6][4] = 1;
frame[6][5] = 1;
frame[6][6] = 1;
frame[6][7] = 1;
frame[6][8] = 1;
frame[6][9] = 1;
frame[7][6] = 1;
}

void timebot(){
timeClient.update();
time_t epochTime2 = timeClient.getEpochTime();
unsigned long epochTime = timeClient.getEpochTime();
while (epochTime < 1707219755) {
epochTime = timeClient.getEpochTime();
delay(25);
}
struct tm *ptm = gmtime ((time_t *)&epochTime2);
int monthDay = ptm->tm_mday;
int aday = timeClient.getDay();
int ahoure = timeClient.getHours();
int aMinute = timeClient.getMinutes();
char timestamp[19];
if(ahoure < 10){
if(aMinute < 10){
snprintf(timestamp, 25, " %s %d - 0%d:0%d", weekday[aday], monthDay,
ahoure, aMinute);
} 
else if(ahoure < 10 && aMinute >= 10) {
snprintf(timestamp, 25, " %s %d - 0%d:%d", weekday[aday], monthDay,
ahoure, aMinute);
}else {
snprintf(timestamp, 25, " %s %d - %d:%d", weekday[aday], monthDay,
ahoure, aMinute);
}} 
else {
if(aMinute < 10){
snprintf(timestamp, 25, " %s %d - %d:0%d", weekday[aday], monthDay,
ahoure, aMinute);
} 
else {
snprintf(timestamp, 25, " %s %d - %d:%d", weekday[aday], monthDay,
ahoure, aMinute);
}}
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(70);
matrix.textFont(Font_5x7);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(timestamp);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
if(ahoure >= 0 && ahoure < 8){ 
wink();
wink2();
nose();
mouth2();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
mouth3();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
mouth2();
matrix.renderBitmap(frame, 8, 12);
delay(500);
}
else {
leftEye();
rightEye();
nose();
mouth();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
wink();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
leftEye();
matrix.renderBitmap(frame, 8, 12);
delay(500);
}}

void setupwelcome(){
matrix.loadFrame(heart);
delay(1000);
matrix.loadFrame(LEDMATRIX_LIKE);
delay(1000);
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(50);
const char text0[] = "  Super Nico  ";
matrix.textFont(Font_4x6);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(text0);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
leftEye();
rightEye();
nose();
mouth();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
wink();
matrix.renderBitmap(frame, 8, 12);
delay(1000);
leftEye();
matrix.renderBitmap(frame, 8, 12);
delay(500);  
}

void smtpCallback(SMTP_Status status);

void smtpCallback(SMTP_Status status){
Serial.println(status.info());
if (status.success()){
Serial.println("----------------");
ESP_MAIL_PRINTF("Message sent success: %d\n", status.completedCount());
ESP_MAIL_PRINTF("Message sent failed: %d\n", status.failedCount());
Serial.println("----------------\n");
for (size_t i = 0; i < smtp.sendingResult.size(); i++){
SMTP_Result result = smtp.sendingResult.getItem(i);
ESP_MAIL_PRINTF("Message No: %d\n", i + 1);
ESP_MAIL_PRINTF("Status: %s\n", result.completed ? "success" : "failed");
ESP_MAIL_PRINTF("Date/Time: %s\n", MailClient.Time.getDateTimeString(result.timestamp, "%B %d, %Y %H:%M:%S").c_str());
ESP_MAIL_PRINTF("Recipient: %s\n", result.recipients.c_str());
ESP_MAIL_PRINTF("Subject: %s\n", result.subject.c_str());
}
Serial.println("----------------\n");
smtp.sendingResult.clear();
}}

void sendstartmail(){
MailClient.networkReconnect(true);
smtp.debug(1);
smtp.callback(smtpCallback);
Session_Config config;
config.server.host_name = SMTP_HOST;
config.server.port = SMTP_PORT;
config.login.email = AUTHOR_EMAIL;
config.login.password = AUTHOR_PASSWORD;
config.login.user_domain = "";
config.time.ntp_server = F("be.pool.ntp.org");
config.time.gmt_offset = 3;
config.time.day_light_offset = 0;
SMTP_Message message;
message.sender.name = F("Arduino");
message.sender.email = AUTHOR_EMAIL;
message.subject = F("Arduino start Email");
message.addRecipient(F(" "), RECIPIENT_EMAIL);
String textMsg = "Bonne journée, je m'appelle Arduino.Je suis un Bot automatique";
message.text.content = textMsg.c_str();
message.text.charSet = "us-ascii";
message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_low;
message.response.notify = esp_mail_smtp_notify_success | esp_mail_smtp_notify_failure | esp_mail_smtp_notify_delay;
if (!smtp.connect(&config)){
ESP_MAIL_PRINTF("Connection error, Status Code: %d, Error Code: %d, Reason: %s", smtp.statusCode(), smtp.errorCode(), smtp.errorReason().c_str());
return;
}
if (!smtp.isLoggedIn()){
Serial.println("\nNot yet logged in.");
}
else{
if (smtp.isAuthenticated())
Serial.println("\nSuccessfully logged in.");
else
Serial.println("\nConnected with no Auth.");
}
if (!MailClient.sendMail(&smtp, &message))
ESP_MAIL_PRINTF("Error, Status Code: %d, Error Code: %d, Reason: %s", smtp.statusCode(), smtp.errorCode(), smtp.errorReason().c_str());  
}

void setup() {
Serial.begin(115200);
matrix.begin();
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(50);
const char text1[] = "    Connexion **********";
matrix.textFont(Font_4x6);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(text1);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
Serial.println("Connecting to: " + String(ssid));
int connectionCounter = 0;
while (status != WL_CONNECTED) {
Serial.print(".");
status = WiFi.begin(ssid, pass);
delay(250);
if ((connectionCounter % 10) == 0) {
Serial.println();
}
connectionCounter++;
}
matrix.beginDraw();
matrix.stroke(0xFFFFFFFF);
matrix.textScrollSpeed(50);
const char text2[] = "    WiFi connecte";
matrix.textFont(Font_4x6);
matrix.beginText(0, 1, 0xFFFFFF);
matrix.println(text2);
matrix.endText(SCROLL_LEFT);
matrix.endDraw();
IPAddress ip = WiFi.localIP();
Serial.println("IP Address: " + ip.toString());
timeClient.begin();
timeClient.setTimeOffset(7200);
setupwelcome();
sendstartmail();
}

void loop(){
timebot();
}
