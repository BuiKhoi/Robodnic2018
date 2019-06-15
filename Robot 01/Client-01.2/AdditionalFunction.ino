void setArmMove(int arm_num, int mode) {
  switch (arm_num) {
    case 0: {
        switch (mode) {
          case 1: {
              digitalWrite(leftArmUp, HIGH);
              digitalWrite(leftArmDown, LOW);
              break;
            }
          case -1: {
              digitalWrite(leftArmUp, LOW);
              digitalWrite(leftArmDown, HIGH);
              break;
            }
          case 0: {
              digitalWrite(leftArmUp, LOW);
              digitalWrite(leftArmDown, LOW);
              break;
            }
        }
        break;
      }

    case 1: {
        switch (mode) {
          case 1: {
              digitalWrite(rightArmUp, HIGH);
              digitalWrite(rightArmDown, LOW);
              break;
            }
          case -1: {
              digitalWrite(rightArmUp, LOW);
              digitalWrite(rightArmDown, HIGH);
              break;
            }
          case 0: {
              digitalWrite(rightArmUp, LOW);
              digitalWrite(rightArmDown, LOW);
              break;
            }
        }
        break;
      }
  }
}

void setPlateMove(int mode) {

  switch (mode) {
    case 1: {
        digitalWrite(plateCW, HIGH);
        digitalWrite(plateCCW, LOW);
        break;
      }
    case 0: {
        digitalWrite(plateCW, LOW);
        digitalWrite(plateCCW, LOW);
        break;
      }
    case -1: {
        digitalWrite(plateCW, LOW);
        digitalWrite(plateCCW, HIGH);
        break;
      }
  }
}

void buzzer(int count, int time) {
  for (int i = 0; i < count; i++) {
    digitalWrite(buzz, HIGH);
    delay(time);
    digitalWrite(buzz, LOW);
    delay(time / 2);
  }
}

void processSwitch(int butt) {
  switch (butt) {
    case 0: {
        if (buttons[0]) {
          digitalWrite(leftArmUp, HIGH);
        } else {
          digitalWrite(leftArmUp, LOW);
        }
        break;
      }
    case 1: {
        if (buttons[1]) {
          digitalWrite(leftArmDown, HIGH);
        } else {
          digitalWrite(leftArmDown, LOW);
        }
        break;
      }
    case 2: {
        if (buttons[2]) {
          digitalWrite(rightArmDown, HIGH);
        } else {
          digitalWrite(rightArmDown, LOW);
        }
        break;
      }
    case 3: {
        if (buttons[3]) {
          digitalWrite(rightArmUp, HIGH);
        } else {
          digitalWrite(rightArmUp, LOW);
        }
        break;
      }
    case 4: {
        if (buttons[4]) {
          digitalWrite(motorRelay[0], HIGH);
          digitalWrite(motorRelay[2], HIGH);
        } else {
          digitalWrite(motorRelay[0], LOW);
          digitalWrite(motorRelay[2], LOW);
        }
        break;
      }
    case 5: {
        if (buttons[5]) {
          digitalWrite(motorRelay[1], HIGH);
          digitalWrite(motorRelay[3], HIGH);
        } else {
          digitalWrite(motorRelay[1], LOW);
          digitalWrite(motorRelay[3], LOW);
        }
        break;
      }
    case 6: {
        static bool count = false;
        if ((count = !count)) {
          digitalWrite(leftPiston, HIGH);
        } else digitalWrite(leftPiston, LOW);
        break;
      }
    case 7: {
        static bool count = false;
        if ((count = !count)) {
          digitalWrite(rightPiston, HIGH);
        } else digitalWrite(rightPiston, LOW);
        break;
      }
    case 8: {
        break;
      }
    case 9: {
        break;
      }
    case 10: {
        if (buttons[10]) {
          digitalWrite(motorRelay[0], HIGH);
          digitalWrite(motorRelay[3], HIGH);
        } else {
          digitalWrite(motorRelay[0], LOW);
          digitalWrite(motorRelay[3], LOW);
        }
        break;
      }
    case 11: {
        if (buttons[11]) {
          digitalWrite(motorRelay[1], HIGH);
          digitalWrite(motorRelay[2], HIGH);
        } else {
          digitalWrite(motorRelay[1], LOW);
          digitalWrite(motorRelay[2], LOW);
        }
        break;
      }
    case 12: {
        static bool count = false;
        if ((count = !count)) {
          digitalWrite(platePiston, HIGH);
        } else {
          digitalWrite(platePiston, LOW);
        }
        break;
      }
    case 13: {
        static bool count = false;
        if ((count = !count)) {
          digitalWrite(pushPiston, HIGH);
        } else {
          digitalWrite(pushPiston, LOW);
        }
        break;
      }
    case 14: {
        break;
      }
    case 15: {
        break;
      }
    case 16: {
        break;
      }
  }
}
