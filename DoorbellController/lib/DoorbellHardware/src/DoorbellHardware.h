#ifndef __DOORBELL_HARDWARE__
#define __DOORBELL_HARDWARE__

#include "Arduino.h"

void setupHardware();

void startMotorOpening();

boolean isButtonPressed();

void startMotorClosing();

#endif
