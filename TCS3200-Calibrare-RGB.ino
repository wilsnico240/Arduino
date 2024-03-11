#define S1 2
#define S0 3
#define S3 4
#define S2 5
#define OUT 6

int redPW = 0;
int greenPW = 0;
int bluePW = 0;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);

  pinMode(OUT, INPUT);

  Serial.begin(9600);
}

void loop() {
  redPW = getRedPW();
  delay(200);

  greenPW = getGreenPW();
  delay(200);

  bluePW = getBluePW();
  delay(200);

  Serial.print("Red PW = ");
  Serial.print(redPW);
  Serial.print(" - Green PW = ");
  Serial.print(greenPW);
  Serial.print(" - Blue PW = ");
  Serial.println(bluePW);
}


int getRedPW() {
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  int PW;
  PW = pulseIn(OUT, LOW);
  return PW;
}

int getGreenPW() {
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  int PW;
  PW = pulseIn(OUT, LOW);
  return PW;
}

int getBluePW() {
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  int PW;
  PW = pulseIn(OUT, LOW);
  return PW;
}

