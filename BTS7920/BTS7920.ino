const byte leftMotor[3] {6, 7};
const byte rightMotor[3] {3, 4};

void setup() {
  for (int i = 0; i < 2; i++) {
    pinMode(leftMotor[i], OUTPUT);
    pinMode(rightMotor[i], OUTPUT);
  }
  delay(1000);
  Serial.begin(9600);
}



void loop() {
  setMotorSpeed(255, 255);
}

void setMotorSpeed(int motor1, int motor2) {

  if (motor1 >= 0) {
    analogWrite(leftMotor[0], motor1);
    digitalWrite(leftMotor[1], LOW);
  } else {
    digitalWrite(leftMotor[0], LOW);
    analogWrite(leftMotor[1], abs(motor1));
  }

  if (motor2 >= 0) {
    analogWrite(rightMotor[0], motor1);
    digitalWrite(rightMotor[1], LOW);
  } else {
    digitalWrite(rightMotor[0], LOW);
    analogWrite(rightMotor[1], 255 + motor1);
  }
}
