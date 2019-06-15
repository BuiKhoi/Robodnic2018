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
        digitalWrite(plateUp, HIGH);
        digitalWrite(plateDown, LOW);
        break;
      }
    case 0: {
        digitalWrite(plateUp, LOW);
        digitalWrite(plateDown, LOW);
        break;
      }
    case -1: {
        digitalWrite(plateUp, LOW);
        digitalWrite(plateDown, HIGH);
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

void constrains(int *motor1, int *motor2) {
  int m1 = *motor1, m2 = *motor2;
  int temp_max = max(m1, m2);
  if (temp_max > 255) {
    m1 = 255 * m1 / temp_max;
    m2 = 255 * m2 / temp_max;
  }

  int temp_min = min(m1, m2);
  if (temp_min < -255) {
    m1 = -255 * m1 / temp_min;
    m2 = -255 * m2 / temp_min;
  }

  *motor1 = m1, *motor2 = m2;
}

void processSwitch(int butt) {
  switch (butt) {
    case 0: case 1: {
        if (buttons[0]) {
          setArmMove(0, -1);
        } else if (buttons[1]) {
          setArmMove(0, 1);
        } else {
          setArmMove(0, 0);
        }
        break;
      }
    case 2: {
        if (buttons[2]) {
          digitalWrite(leftPiston, HIGH);
        } else digitalWrite(leftPiston, LOW);
        break;
      }
    case 3: {
        if (buttons[3]) {
          digitalWrite(rightPiston, HIGH);
        } else digitalWrite(rightPiston, LOW);
        break;
      }
    case 4: case 5: {
        if (buttons[4]) {
          setArmMove(1, -1);
        } else if (buttons[5]) {
          setArmMove(1, 1);
        } else {
          setArmMove(1, 0);
        }
        break;
      }
    case 6: {
        if (buttons[6]) {
          digitalWrite(pushPiston, HIGH);
        } else digitalWrite(pushPiston, LOW);
        break;
      }
    case 7: {
        if (buttons[7]) {
          digitalWrite(leftArmPiston, HIGH);
        } else digitalWrite(leftArmPiston, LOW);
        break;
      }
    case 8: {
        if (buttons[8]) {
          digitalWrite(rightArmPiston, HIGH);
        } else digitalWrite(rightArmPiston, LOW);
        break;
      }
    case 9: {
        if (!buttons[9]) {
          digitalWrite(platePiston, HIGH);
        } else digitalWrite(platePiston, LOW);
        break;
      }
    case 10: {
        if (buttons[10]) {
          resetFunc();
        }
        break;
      }
    case 11: {
        break;
      }
    case 12: {
        break;
      }
    case 13: {
        digitalWrite(motorRelay[0], HIGH);
        digitalWrite(motorRelay[1], LOW);
        break;
      }
    case 14: {
        digitalWrite(motorRelay[0], LOW);
        digitalWrite(motorRelay[1], HIGH);
        break;
      }
    case 15: {
        digitalWrite(motorRelay[2], HIGH);
        digitalWrite(motorRelay[3], LOW);
        break;
      }
    case 16: {
        digitalWrite(motorRelay[2], HIGH);
        digitalWrite(motorRelay[3], LOW);
        break;
      }
  }
}

void removeFirstElement(byte *arr, byte *count) {
  for (int i = 0; i < *count; i++) {
    arr[i] = arr[i + 1];
  }
  (*count) -= 1;
}

void processSwitchBuffer() {
  if (buttonsBufferCountHigh > 0) {
    processSwitch(buttonsBufferHigh[0]);
    removeFirstElement(buttonsBufferHigh, &buttonsBufferCountHigh);
  }

  if (buttonsBufferCountLow > 0) {
    processSwitch(buttonsBufferLow[0]);
    removeFirstElement(buttonsBufferLow, &buttonsBufferCountLow);
  }
}

