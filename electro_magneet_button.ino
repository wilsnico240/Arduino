const int buttonPin = 4; 
const int magnetPin = 5; 
int buttonState = 0; 
int lastButtonState = 0; 
bool magnetState = false; 

void setup() {
pinMode(buttonPin, INPUT_PULLUP); 
pinMode(magnetPin, OUTPUT); 
digitalWrite(magnetPin, LOW);
}

void loop() {
buttonState = digitalRead(buttonPin);
if (buttonState == LOW && lastButtonState == HIGH) {
delay(50);
magnetState = !magnetState;
if (magnetState) {
digitalWrite(magnetPin, HIGH);
} 
else {
digitalWrite(magnetPin, LOW);
}}
lastButtonState = buttonState;
}
