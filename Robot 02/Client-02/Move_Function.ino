void moveRobot() {
  int m1, m2, m3, m4;
  int pid_value = 0;

//  if (abs(channels[3]) <= 10) {
//    pid_value = pidCalc();
//  }
//  else {
//    comp_angle = filter.updateEstimate(compass.readRaw().XAxis);
//  }

  m1 = channels[1];
  m2 = channels[1];
  m3 = channels[1];
  m4 = channels[1];

  m1 += channels[2];
  m2 -= channels[2];
  m3 -= channels[2];
  m4 += channels[2];

  m1 += channels[3] + pid_value;
  m2 -= channels[3] + pid_value;
  m3 += channels[3] + pid_value;
  m4 -= channels[3] + pid_value;

  setMotorSpeed(m1, m2, m3, m4);
}
