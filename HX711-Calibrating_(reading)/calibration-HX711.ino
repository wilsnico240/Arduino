//calibration will be  "(reading result)/(known weight)=(result)" => in weighting script "scale.set_scale(result);"
#include "HX711.h"

const int LOADCELL_DOUT_PIN = 4;
const int LOADCELL_SCK_PIN = 5;

HX711 scale;

void setup() {
  Serial.begin(9600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
}

void loop() {

    scale.set_scale();    
    Serial.println("Remove any weights from the scale !!!");
    delay(10000);
    Serial.println("Tare reading :");
    delay(1000);
    scale.tare();
    Serial.println("Tare done !!!");
    delay(1000);
    Serial.println("Place a known weight on the scale.");
    delay(5000);
    Serial.println("Rreading !");
    delay(1000);
    long reading = scale.get_units(10);
    Serial.println("Rreading result: ");
    Serial.print(reading);
    Serial.println();
    Serial.println();
    delay(3000);
}
