void shiftSpeed(int state) {
  static int speedState = 0;
  if (state != speedState) {
    Serial.println(state);
    switch (state) {
      case 0: {
          digitalWrite(shiftSpeed01, LOW);
          break;
        }
      case 1: {
          digitalWrite(shiftSpeed01, HIGH);
          break;
        }
      default: {
          digitalWrite(shiftSpeed01, LOW);
          break;
        }
    }
    speedState = state;
  }
}

void moveRobot() {
  static bool written = false;
  if (buttonStateChange) {
    if (buttons[10]) {
      if (buttons[4] || buttons[5]) {
        shiftSpeed(0);
        digitalWrite(motorRelay[0], LOW);
        digitalWrite(motorRelay[1], HIGH);
        digitalWrite(motorRelay[2], HIGH);
        digitalWrite(motorRelay[3], LOW);
      } else {
        digitalWrite(motorRelay[1], LOW);
        digitalWrite(motorRelay[2], LOW);
      }
    } else if (buttons[11]) {
      if (buttons[4] || buttons[5]) {
        shiftSpeed(0);
        digitalWrite(motorRelay[0], HIGH);
        digitalWrite(motorRelay[1], LOW);
        digitalWrite(motorRelay[2], LOW);
        digitalWrite(motorRelay[3], HIGH);
      } else {
        digitalWrite(motorRelay[0], LOW);
        digitalWrite(motorRelay[3], LOW);
      }
    } else if (buttons[4]) {
      shiftSpeed(1);
      digitalWrite(motorRelay[0], HIGH);
      digitalWrite(motorRelay[2], HIGH);
    } else if (buttons[5]) {
      shiftSpeed(1);
      digitalWrite(motorRelay[1], HIGH);
      digitalWrite(motorRelay[3], HIGH);
    } else if (!written) {
      digitalWrite(motorRelay[0], LOW);
      digitalWrite(motorRelay[1], LOW);
      digitalWrite(motorRelay[2], LOW);
      digitalWrite(motorRelay[3], LOW);
      written = true;
      return;
    }
    written = false;
  }
}
