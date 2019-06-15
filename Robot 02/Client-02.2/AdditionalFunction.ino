void setMotorSpeed(int m1, int m2, int m3, int m4) {
  //Shift speed value to motor driver
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
  //Set arm move up, down or stop
  switch (mode) {
      Serial.println(mode);
    case -1: {
        digitalWrite(pullArmDown, HIGH);
        digitalWrite(pullArmUp, LOW);
        break;
      }
    case 0: {
        digitalWrite(pullArmDown, LOW);
        digitalWrite(pullArmUp, LOW);
        break;
      }
    case 1: {
        digitalWrite(pullArmDown, LOW);
        digitalWrite(pullArmUp, HIGH);
        break;
      }
  }
}

int pidCalc() {
  //calculate PID value
  static float prev_error, prev_i;
  static int prev_loop = 0;
  float error, pid_value, i_error, d_error;
  static int loop_time = 0;

  if (millis() - prev_loop > 200) {
    error = getDifferental();
    Serial.println(error);
    i_error = error + prev_i;
    d_error = error - prev_error;

    prev_i = i_error;
    prev_error = error;

    pid_value = kP * error + kI * i_error + kD * d_error;
    prev_loop = millis();
    return (int) - pid_value;
  } else {
    return 0;
  }
}

float getDifferental() {
  float differental = getHeading() - first_angle;
  if (abs(differental) > PI) {
    int temp = differental / abs(differental);
    differental = 2 * PI - abs(differental);
    differental *= temp;
  }
  return differental;
}

float getHeading() {
  Vector norm = compass.readNormalize();
  float heading = atan2(norm.YAxis, norm.XAxis);
  float declinationAngle = (-1.0 + (12.0 / 60.0)) / (180 / M_PI);
  heading += declinationAngle;
  if (heading < 0)
  {
    heading += 2 * PI;
  }

  if (heading > 2 * PI)
  {
    heading -= 2 * PI;
  }
  return heading;
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
  //Make sure motor value is valid and in a correct ratio
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
  //Process switch events
  Serial.println(butt);
  switch (butt) {
    case 0: {
        static bool count = false;
        if ((count = !count)) {
          digitalWrite(highHand, HIGH);
        } else {
          digitalWrite(highHand, LOW);
        }
        break;
      }
    case 1: {
        if (buttons[1]) {
          digitalWrite(pulloutArm, LOW);
        } else {
          digitalWrite(pulloutArm, HIGH);
        }
        break;
      }
    case 2: {
        if (buttons[2]) {
          setArmMove(-1);
        } else setArmMove(0);
        break;
      }
    case 3: {
        if (buttons[3]) {
          setArmMove(1);
        } else setArmMove(0);
        break;
      }
    case 4: {
        break;
      }
    case 5: {
        break;
      }
    case 6: {
        break;
      }
    case 7: {
        break;
      }
    case 8: {
        static bool count = false;
        if ((count = !count)) {
          digitalWrite(upperHand, HIGH);
        } else {
          digitalWrite(upperHand, LOW);
        }
        break;
      }
    case 9: {
        static bool count = false;
        if ((count = !count)) {
          digitalWrite(lowerHand, HIGH);
        } else {
          digitalWrite(lowerHand, LOW);
        }
        break;
      }
    case 10: {
        static bool count = false;
        if ((count = !count)) {
          digitalWrite(pushArm, HIGH);
        } else {
          digitalWrite(pushArm, LOW);
        }
        break;
      }
    case 11: {
        static bool count = false;
        if ((count = !count)) {
          digitalWrite(moveArm, HIGH);
        } else {
          digitalWrite(moveArm, LOW);
        }
        break;
      }
    case 12: {
        break;
      }
  }
}
