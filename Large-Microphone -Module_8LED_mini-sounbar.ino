int sensorPin = A0;
int sensorValue = 0;
int percentage;
int ledPins[] = {4, 5, 6, 7, 8, 9, 10, 11};

void setup(){
  Serial.begin(9600);
  for(int i=0; i<8; i++){
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
}

void loop(){
  sensorValue = analogRead(sensorPin);
  percentage = map(sensorValue, 225,300, 0, 100);
  
  for(int i=0; i<8; i++){
    if(percentage >= ((i+1)*12.5)){
      digitalWrite(ledPins[i], HIGH);
    } else {
      digitalWrite(ledPins[i], LOW);
    }
  }
}
