#define shiftSpeed01 7
#define shiftSpeed02 6

const int motorRelay[2] = {27, 29};

void setup() {
  Serial.begin(9600);
  pinMode(shiftSpeed01, OUTPUT);
  pinMode(shiftSpeed02, OUTPUT);

  for (int i = 0; i < 2; i++) {
    pinMode(motorRelay[i], OUTPUT);
  }
}

void loop() {
  digitalWrite(motorRelay[0], LOW);
  digitalWrite(shiftSpeed01, LOW);
  digitalWrite(motorRelay[1], LOW);
  digitalWrite(shiftSpeed02, LOW);
}

void setMotorSpeed(int m1, int m2) {
  if (m1 >= 0) {
    digitalWrite(motorRelay[0], HIGH);
    digitalWrite(shiftSpeed01, LOW);
  } else {
    digitalWrite(motorRelay[0], LOW);
    analogWrite(shiftSpeed01, 255 + m1);
  }

  if (m2 >= 0) {
    digitalWrite(motorRelay[1], HIGH);
    analogWrite(shiftSpeed02, m2);
  } else {
    digitalWrite(motorRelay[1], LOW);
    analogWrite(shiftSpeed02, 255 + m2);
  }
}

