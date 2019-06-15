void setMotorSpeed(int m1, int m2, int m3, int m4) {
  constrains(&m1, &m2, &m3, &m4);

  if (m1 >= 0) {
    analogWrite(motor1[0], m1);
    digitalWrite(motor1[1], LOW);
  } else {
    digitalWrite(motor1[0], LOW);
    analogWrite(motor1[1], abs(m1));
  }

  if (m2 >= 0) {
    analogWrite(motor2[0], m2);
    digitalWrite(motor2[1], LOW);
  } else {
    digitalWrite(motor2[0], LOW);
    analogWrite(motor2[1], abs(m2));
  }

  if (m3 >= 0) {
    analogWrite(motor3[0], m3);
    digitalWrite(motor3[1], LOW);
  } else {
    digitalWrite(motor3[0], LOW);
    analogWrite(motor3[1], abs(m3));
  }

  if (m4 >= 0) {
    analogWrite(motor4[0], m4);
    digitalWrite(motor4[1], LOW);
  } else {
    digitalWrite(motor4[0], LOW);
    analogWrite(motor4[1], abs(m4));
  }

//  Serial.print(m1);
//  Serial.print("  ");
//  Serial.print(m2);
//  Serial.print("  ");
//  Serial.print(m3);
//  Serial.print("  ");
//  Serial.println(m4);
}

void setArmMove(int mode) {
  switch (mode) {
    case -1: {
        digitalWrite(pullArmDown, LOW);
        digitalWrite(pullArmUp, HIGH);
        break;
      }
    case 0: {
        digitalWrite(pullArmDown, HIGH);
        digitalWrite(pullArmUp, HIGH);
        break;
      }
    case 1: {
        digitalWrite(pullArmDown, HIGH);
        digitalWrite(pullArmUp, LOW);
        break;
      }
  }
}

int pidCalc() {
  static float prev_error, prev_i;
  static boolean prev_loop = false;
  float error, pid_value, i_error, d_error;

  if (prev_loop) {
    error = getDifferental();
    i_error = error + prev_i;
    d_error = error - prev_error;

    prev_i = i_error;
    prev_error = error;

    pid_value = kP * error + kI * i_error + kD * d_error;

    return (int) pid_value;
  } else {
    prev_loop = true;
    return 0;
  }
}

int getDifferental() {
  return filter.updateEstimate(compass.readRaw().XAxis) - comp_angle;
}

void buzzer(int count, int time) {
  for (int i = 0; i < count; i++) {
    digitalWrite(buzz, HIGH);
    delay(time);
    digitalWrite(buzz, LOW);
    delay(time / 2);
  }
}

void constrains(int *motor1, int *motor2, int *motor3, int *motor4) {
  int m1 = *motor1, m2 = *motor2, m3 = *motor3, m4 = *motor4;
  int maxx = m1 > m2 ? m1 : m2;
  maxx = (maxx > m3) ? maxx : m3;
  maxx = (maxx > m4) ? maxx : m4;

  if (maxx > 255) {
    m1 = (int)255 * (float)m1 / maxx;
    m2 = (int)255 * (float)m2 / maxx;
    m3 = (int)255 * (float)m3 / maxx;
    m4 = (int)255 * (float)m4 / maxx;
  }

  int minn = m1 < m2 ? m1 : m2;
  minn = (minn < m3) ? minn : m3;
  minn = (minn < m4) ? minn : m4;

  if (minn < -255) {
    m1 = (int) - 255 * (float)m1 / minn;
    m2 = (int) - 255 * (float)m2 / minn;
    m3 = (int) - 255 * (float)m3 / minn;
    m4 = (int) - 255 * (float)m4 / minn;
  }

  *motor1 = m1;
  *motor2 = m2;
  *motor3 = m3;
  *motor4 = m4;
}

void processSwitch(int butt) {
  switch (butt) {
    case 0: {
        if (buttons[0]) {
          setArmMove(-1);
        }
        else setArmMove(0);
        break;
      }
    case 1: {
        if (buttons[1]) {
          setArmMove(1);
        } else setArmMove(0);
      }
    case 2: {
        break;
      }
    case 3: {
        break;
      }
    case 4: {
        if (buttons[4]) {
          digitalWrite(lowerHand, LOW);
        } else digitalWrite(lowerHand, HIGH);
        break;
      }
    case 5: {
        if (buttons[5]) {
          digitalWrite(upperHand, LOW);
        } else digitalWrite(upperHand, HIGH);
        break;
      }
    case 6: {
        break;
      }
    case 7: {
        if (buttons[7]) {
          digitalWrite(moveArm, LOW);
        } else digitalWrite(moveArm, HIGH);
        break;
      }
    case 8: {
        if (buttons[8]) {
          digitalWrite(pulloutArm, LOW);
        } else digitalWrite(pulloutArm, HIGH);
        break;
      }
    case 9: {
        if (buttons[9]) {
          digitalWrite(pushArm, LOW);
        } else digitalWrite(pushArm, HIGH);
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
