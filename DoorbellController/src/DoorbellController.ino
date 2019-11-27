#include "DoorbellHardware.h"

const String topic = "IoTDoorbell";
bool shouldPublish = false;           //whether the program should call publishState
enum doorStatus {
  OPEN,
  CLOSED,
};
doorStatus doorState;
bool isUIClicked = false;             //whether the user click the door button in the UI
bool isLocked = true;                 //lock state

//set UIClicked to true if the user click the door button in the UI
int doorButtonPress(String nothing) {
  isUIClicked = true;
  return 0;
}

//toggle lock
int lockButtonPress(String nothing) {
  if (isLocked) {
    unlockDoor();
  } else {
    lockDoor();
  }
  isLocked = !isLocked;
  shouldPublish = true;
  return 0;
}

//publish data to cloud:
// +/ doorState
// +/ isLocked
int publishState(String nothing) {
  String data = "{\"doorState\":";

  if (doorState == OPEN) {
      data += "\"Open\"";
  }
  else if (doorState == CLOSED) {
      data += "\"Closed\"";
  }
  data += ", ";
  data += "\"isLocked\":";
  if (isLocked) {
      data += "true";
  } else {
      data += "false";
  }
  data += "}";

  Serial.println("Publishing:");
  Serial.println(data);
  Particle.publish(topic, data, 60, PRIVATE);
  return 0;
}

void setup() {
  setupHardware();
  //set initial state of door
  doorState = CLOSED;

  Particle.function("publishState", publishState);
  Particle.function("doorButtonPress", doorButtonPress);
  Particle.function("lockButtonPress", lockButtonPress);
}

//variables for debounce
unsigned long lastPressTime = 0;
const unsigned long debounceDelay = 100;
bool lastState = false;
bool alreadyDone = false;


void loop() {
  unsigned long currentMillis = millis();
  bool isPressedDoor = isButtonPressed();

  if (shouldPublish) {
    publishState("");
    shouldPublish = false;
  }

  switch (doorState) {
    case OPEN:
      if (isPressedDoor && lastPressTime + debounceDelay <= currentMillis && !alreadyDone) {
        alreadyDone = true;
      }

      else if (!isPressedDoor && lastState) {
        lastState = false;
        alreadyDone = false;
      }

      else if(isPressedDoor && !lastState) {
        lastState = true;
        lastPressTime = currentMillis;
      }

      if (isUIClicked) {
        isUIClicked = false;
        shouldPublish = true;
        doorState = CLOSED;
        startMotorClosing();
      }

      break;

    case CLOSED:
      if (isPressedDoor  && lastPressTime + debounceDelay <= currentMillis && !alreadyDone) {
        alreadyDone = true;
        Particle.publish("Notification", "Ringing", 60, PRIVATE);
      }

      else if (!isPressedDoor  && lastState) {
        lastState = false;
        alreadyDone = false;
      }

      else if(isPressedDoor  && !lastState) {
        lastState = true;
        lastPressTime = currentMillis;
      }

      if (isUIClicked) {
        isUIClicked = false;
        shouldPublish = true;
        doorState = OPEN;
        startMotorOpening();
      }

      break;
  }

}
