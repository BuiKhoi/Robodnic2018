const int motor[2] = {10, 11};

void setup() {
  for (int i = 0; i < 2; i++) {
    pinMode(motor[i], OUTPUT);
  }
}

void loop() {
  for (int i = -255; i < 0; i += 10) {
    analogWrite(motor[1], abs(i));
    digitalWrite(motor[0], LOW);
    delay(200);
  }

  for (int i = 0; i < 255; i += 10) {
    analogWrite(motor[0], i);
    digitalWrite(motor[1], LOW);
    delay(200);
  }

  for (int i = 255; i >0 ; i -= 10) {
    analogWrite(motor[0], i);
    digitalWrite(motor[1], LOW);
    delay(200);
  }

  for (int i = 0; i >-255; i -= 10) {
    analogWrite(motor[1], abs(i));
    digitalWrite(motor[0], LOW);
    delay(200);
  }
}
