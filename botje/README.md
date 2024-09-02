Botje, Interactive Arduino R4 WiFi Desktop Companion

Bill Gates way, so all programmers of Flappy, Snake, ... you recognize something from you, I don't deny it and I am grateful for your....

Story

R4 WiFi collection of what I found on the net throwed together with some stuff from me in an interactive companion with the following skills :

Funny animation & images .

Old scool retro sounds .

Time bound atmosphere mood 16x16 LED Matrix .

Animated R4 LED Matrix Face .(Sleeps from midnight to 8 am morning.)

Local measurements of temperature, humidity, pressure, air particles, UV index.

Online time/date & weather information .

50 questions Trivia, Snake & Flappy Game .

Online question, answer jokes .

Is in French, but not difficult to convert all French -speaking text with translator to ....

Not completely, still small problems.Sweet programmers You can be useful here, all help is welcome .

WiFi Connection ;

Change .

char ssid[] = "--------";

char pass[] = "--------";

For correct time, change time zone :

Change .

timeClient.setTimeOffset(7200);

You can also change the NTP server in this line :

NTPClient timeClient(ntpUDP, "be.pool.ntp.org");

Forecast coordinates :

Change latitude, longitude in (First check on open-meteo coordinates .) .

client.println("GET /v1/forecast?latitude=50.6337&longitude=5.5675&current=temperature_2m,relative_humidity_2m,apparent_temperature,is_day,precipitation,rain,showers,snowfall,weather_code,cloud_cover,pressure_msl,surface_pressure,wind_speed_10m,wind_direction_10m,wind_gusts_10m&timezone=Europe%2FBerlin&forecast_days=1 HTTP/1.1");

Name city of forecast chosen coordinates, (4 times to change) :

Change .

u8g2.print("-Liege-");

English version of jokes :

Change .

clientssl.println("GET /joke/Any?lang=fr&format=xml&type=twopart HTTP/1.1");

To .

clientssl.println("GET /joke/Any?lang=en&format=xml&type=twopart HTTP/1.1");

install libraries :

U8g2lib.h, Wire.h, WiFiS3.h, WiFiSSLClient.h, IPAddress.h, ArduinoJson.h, assert.h,

ArduinoGraphics.h, Arduino_LED_Matrix.h, FastLED.h, NTPClient.h, WiFiUdp.h,

RTC.h, Adafruit_BMP085_U.h, Adafruit_Sensor.h, MQSpaceData.h, DHT.h

All files in one compressed version(zip, 29 items) .

Latest update :

1/09/2004

https://drive.google.com/file/d/1M24QfCl-ZWanTMS8OWhh0rGcJ9PcwkZl/view

All videos may have different images or animation than the latest version of Project !!!!!!!

video Botje :

https://drive.google.com/file/d/1vl_shGyRmG-MU7OvcF3XYa6gA5LfyKxH/view

Video face R4 LED matrix :

https://drive.google.com/file/d/1yig8mSmTFw5lun-mWuM3_O87Oeiy0pP0/view

Video humidity and temperature :

https://drive.google.com/file/d/1aBAI_t65RNd9fRXFwBRJPth4M25G156c/view

Video UV index and pressure :

https://drive.google.com/file/d/1LpiWilkduq1KFA-Lj1tmkBKxas_EQVvB/view

Video MQ Sensors ( MQ Sensors are plug &;Play method. Do not forget necessary warming up time for MQ) and Open-Meteo.com :

https://drive.google.com/file/d/1h5M30COtwtHP1VNPKTO3ywfonnDyZlR2/view

Video Date - Time and Ttrivia Game :

https://drive.google.com/file/d/1Y4cCrgWzf2OU70jLsUPV0PXotMEPscGK/view

Video Snake and Flappy Game :

https://drive.google.com/file/d/1PLZREkEb9nalueP9ZfUnfH3-CecwNFvN/view

video matrix animation RTC-time= >12h<14h :

https://drive.google.com/file/d/1mEuzJQIFTs2Ansyr7R7T62vk_mo6Ip8x/view

video matrix animation RTC-time= >8h<12h & >14h<19h :

https://drive.google.com/file/d/1iJbZ4yMAHCe_uXH_kTfQ2giFJB446xlO/view

video matrix animation RTC-time= >19h<24h :

https://drive.google.com/file/d/1sjIwmtOUvf0dWBG2_UMgHp9MnlAZQeio/view

video matrix animation RTC-time= >24h<8h :

https://drive.google.com/file/d/1gqXVF857WY0UBUrHS5Wt1dgUXXaX3QZN/view

video matrix2 time (Less LED brightness between 7 pm and midnight, no time display between midnight and 8 am) :

https://drive.google.com/file/d/1IaMvuwuGBaxWwustG0aPGT0Op17hN8vE/view

---Final OLED image an animation videos (Update 27/08/2004)--

Online question, answer joke loop from v2.jokeeapi.dev on OLED (No joke 24pm/8am):

https://drive.google.com/file/d/12YEfJtUsX01AequNvzqSQ_ctmvFmd4Wf/view

Botje OLED Start Animation :

https://drive.google.com/file/d/1XCMvBs51Z8Zah7KnP9hYtEd8Kjl3-h75/view

Open-meteo animation and data :

https://drive.google.com/file/d/1MGj0vCfuj1C9yu4BGN_FDkc1XocyG4JV/view

Month calendar :

https://drive.google.com/file/d/1OpRrmqjVF3L5-lPZKZ5LFg-hPOmJUdI0/view

Trivia Coornrect Answered Animation :

https://drive.google.com/file/d/1S-H6jGUSuoCg1ZW_8W-NODkONzi5qmAh/view

Trivia Wrong answer image :

https://drive.google.com/file/d/1Rw-LrRvravq3aGwfc3EUOTz7s1jUKJ_n/view

Flappy game title and game over images :

https://drive.google.com/file/d/17JNX7AwiCFslq2LL4Fl_3MqLBRgx9J6a/view

Snake game title and game over images :

https://drive.google.com/file/d/1B48QOGezjHesQIc8wZLghP3DnTz1CdIK/view

Things used in this project

Hardware components

Arduino UNO R4 WiFi ×	1	

GUVA-S12SD	×	1		

MQ-8	×	1		

MQ-7	×	1		

MQ-6	×	1	

MQ-5	×	1		

MQ-4	×	1		

MQ-3	×	1		

MQ-2	×	1	

MQ-135	×	1	

Modulo Joystick	×	1		

KY-004	×	4	

128X128 oled	×	1	

RGB LED matrix 16X16	×	1	

Loudspeaker, 2W	 ×	1		

relay module	×	1	

DHT22 Temperature Sensor	×	1	

traffic light	×	1	

BMP180	×	1	

Male/Female Jumper Wires	×	1	

Male/Male Jumper Wires	×	1	

Toy car flashing light	×	1		

5v mini cooling fan	×	1	

Breadboard (generic) Big	×	1	

Solderless Breadboard Half Size		×	1	

OPEN-SMART I2C LED MATRIX 16x8	×	1	

![20240830_214122_S2GmDFPjBj](https://github.com/user-attachments/assets/51efaeba-3f2d-4d34-9464-39c3b797964f)

![20240825_112453_nSvVhsf0Xi](https://github.com/user-attachments/assets/c23be584-92ea-437a-8313-edb90c6c4e22)

![20240825_112421_bhYA4u3a8h](https://github.com/user-attachments/assets/b3dccf95-4989-48f2-a5d2-1efb8a4893d7)

![20240825_112410_AsxtZzAgZV](https://github.com/user-attachments/assets/47e82763-a2eb-4360-92c1-9ca83feb3d9b)

![20240825_112410_AsxtZzAgZ2V](https://github.com/user-attachments/assets/809e8181-7a62-4a23-941c-6dc109d21419)

![20240825_112415_lTQCDmtFKk](https://github.com/user-attachments/assets/85cd4fe2-6203-4d11-849a-7cde1b749aae)

![20240825_112431_35CZYHJ8GY](https://github.com/user-attachments/assets/7c3052a3-50c6-4cdf-b214-15e2f9663e75)

![20240825_112447_6sLSS0cPhi](https://github.com/user-attachments/assets/3a76f740-98be-48bf-9340-cf0c448b0b34)

![20240825_112512_gZkfNRhVbP](https://github.com/user-attachments/assets/b59c879d-7101-4f4b-9539-a068261825c3)

![20240830_162324_FHmaGifDek](https://github.com/user-attachments/assets/a5b4bf2c-7e33-4f61-a4f0-1bc8ba03fc53)

![20240825_153054_Q4oAct1g9t](https://github.com/user-attachments/assets/413abde5-f9dd-4555-b155-1dce27a4e142)

![20240825_141930_Ykwmb4Gbbn](https://github.com/user-attachments/assets/b22e248b-8bb5-4270-a1d3-5a45ec73765b)

![20240825_133604_CRK07SUE2y](https://github.com/user-attachments/assets/2eec70d5-f785-41fe-a3c4-6dc37782bb0a)

![20240825_133557_QOow1LIx8B](https://github.com/user-attachments/assets/d47c307e-c30d-46d9-ad0c-aa519f4f952a)

![1000023195](https://github.com/user-attachments/assets/74d35b5d-a592-4323-9362-ac4b9e1751e4)

![20240825_133548_oJ8ODCWfEW](https://github.com/user-attachments/assets/ec9aafaf-7336-4eac-8e28-4180b656a844)

![20240825_112601_KbFX0tujju](https://github.com/user-attachments/assets/2d37acf3-a2df-43a4-bfa2-4644010d8927)

