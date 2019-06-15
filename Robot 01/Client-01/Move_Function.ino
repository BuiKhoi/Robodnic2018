void adjustSpeed() {
  if (channels[0] > -200 && channels[0] <= -180) {
    analogWrite(motor[0], 85);
    digitalWrite(motor[1], LOW);
  } else if (channels[0] > -180 && channels[0] <= 180) {
    analogWrite(motor[0], 170);
    digitalWrite(motor[1], LOW);
  } else {
    analogWrite(motor[0], 255);
    digitalWrite(motor[1], LOW);
  }
}

void moveSpinningPlate() {
  if (abs(channels[3]) >= 100) {
    setPlateMove(channels[3] / abs(channels[3]));
  } else setPlateMove(0);
}

