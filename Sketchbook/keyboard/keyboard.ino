#include "Keyboard.h"
const int buttonPin = 0;

void setup() {
  pinMode(buttonPin, INPUT);
  Keyboard.begin();
}

void loop() {
    if (digitalRead(buttonPin) == HIGH) {
      Keyboard.print("Henlo");
      delay(200);
    }
}
