#include "DoorbellHardware.h"

const String topic = "IoTDoorbell";
bool shouldPublish = false;           //whether the program should call publishState
enum doorStatus {
  OPEN,
  CLOSED,
};
doorStatus doorState;
bool isUIClicked = false;             //whether the user click the door button in the UI


//set UIClicked to true if the user click the door button in the UI
int doorButtonPress(String nothing) {
    isUIClicked = true;
    return 0;
}

int publishState(String nothing) {
  String data = "{\"doorState\":";

  if (doorState == OPEN) {
      data += "\"Open\"";
  }
  else if (doorState == CLOSED) {
      data += "\"Closed\"";
  }
  data += "}";

  Serial.println("Publishing:");
  Serial.println(data);
  Particle.publish(topic, data, 60, PRIVATE);
  return 0;
}

void setup() {
  setupHardware();
  //get the initial state of the door
  doorState = CLOSED;

  Particle.function("publishState", publishState);
  Particle.function("doorButtonPress", doorButtonPress);
}

//variables for debounce
unsigned long lastPressTime = 0;
const unsigned long debounceDelay = 100;
bool lastState = false;
bool alreadyDone = false;

void loop() {
  unsigned long currentMillis = millis();
  bool isPressed = isButtonPressed();

  if (shouldPublish) {
    publishState("");
    shouldPublish = false;
  }

  switch (doorState) {
    case OPEN:
      if (isPressed && lastPressTime + debounceDelay <= currentMillis && !alreadyDone) {
        alreadyDone = true;
        shouldPublish = true;
      }

      else if (!isPressed && lastState) {
        lastState = false;
        alreadyDone = false;
      }

      else if(isPressed && !lastState) {
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
      if (isPressed && lastPressTime + debounceDelay <= currentMillis && !alreadyDone) {
        alreadyDone = true;
        shouldPublish = true;
        Particle.publish("Notification", "Ringing", 60, PRIVATE);
      }

      else if (!isPressed && lastState) {
        lastState = false;
        alreadyDone = false;
      }

      else if(isPressed && !lastState) {
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
