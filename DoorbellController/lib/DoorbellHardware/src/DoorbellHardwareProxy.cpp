#if 1
#include "Arduino.h"
#include "DoorbellHardware.h"

const int piezo = D0;
const int doorController = D3;
const int lockController = D4;
const int lockLight = D1;
Servo door;

//setup hardware when first begins
void setupHardware() {
  Serial.begin(9600);
  pinMode(doorController, INPUT_PULLUP);
  pinMode(lockController, INPUT_PULLUP);
  pinMode(lockLight, OUTPUT);
  digitalWrite(lockLight, HIGH);
  door.attach(D2);
  door.write(0);
}

//whether the bell is pressed
boolean isButtonPressed() {
  if (digitalRead(doorController) == 0) {
    Serial.println("here");
    tone(piezo, 4000, 100);
    return true;
  }
  return false;
}

//open the door
void startMotorOpening() {
  door.write(120);
}

//close the door
void startMotorClosing() {
  door.write(0);
}

//lock the door
void lockDoor() {
  digitalWrite(lockLight, HIGH);
}

//unlock the door
void unlockDoor() {
  digitalWrite(lockLight, LOW);
}

#endif
