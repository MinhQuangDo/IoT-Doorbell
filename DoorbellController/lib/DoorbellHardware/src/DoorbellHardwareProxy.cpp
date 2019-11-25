#if 1
#include "Arduino.h"
#include "DoorbellHardware.h"

const int doorController = D3;
Servo door;

void setupHardware() {
  Serial.begin(9600);
  pinMode(doorController, INPUT_PULLUP);
  door.attach(D0);
  door.write(0);
}

boolean isButtonPressed() {
  return digitalRead(doorController) == 0;
}

void startMotorOpening() {
  door.write(120);
}

void startMotorClosing() {
  door.write(0);
}

#endif
