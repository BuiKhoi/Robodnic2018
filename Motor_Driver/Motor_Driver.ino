const int motor1[3] = {7, 8, 5};
const int motor2[3] = {4, 9, 6};

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(motor1[i], OUTPUT);
    pinMode(motor2[i], OUTPUT);
  }
}

void loop() {
  //  setMotorSpeed(255, 255);
  //  delay(2000);
  setMotorSpeed(-255, 255);
  delay(2000);
}

void setMotorSpeed(int m1, int m2) {
  if (m1 >= 0) {
    digitalWrite(motor1[0], HIGH);
    digitalWrite(motor1[1], LOW);
    analogWrite(motor1[2], m1);
  } else {
    digitalWrite(motor1[0], LOW);
    digitalWrite(motor1[1], HIGH);
    analogWrite(motor1[2], abs(m1));
  }

  if (m2 >= 0) {
    digitalWrite(motor2[0], HIGH);
    digitalWrite(motor2[1], LOW);
    analogWrite(motor2[2], m2);
  } else {
    digitalWrite(motor2[0], LOW);
    digitalWrite(motor2[1], HIGH);
    analogWrite(motor2[2], abs(m2));
  }
}

