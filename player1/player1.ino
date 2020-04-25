#include <Wire.h>

void setup() {
  Serial.begin(9600);
  Wire.begin(7);           
  Wire.onRequest(requestEvent); 
}

void loop() {
  delay(100);
}

void requestEvent() {

  int position;
  if(Serial.available() >0) {
    position = Serial.read();
    if((position > 48) && (position < 58)) {
      Wire.write(position-48);
      Serial.println(position-48);
    }
  }
}
