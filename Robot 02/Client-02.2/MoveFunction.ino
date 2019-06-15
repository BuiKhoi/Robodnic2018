void moveRobot() {
  //Process speed value for mecanum wheels with PID value
  int m1, m2, m3, m4;
  int pid_value = 0;

  if (abs(channels[2]) <= 20) {
    pid_value = pidCalc();
  }
  else {
    first_angle = getHeading();
  }

  m1 = channels[0];
  m2 = channels[0];
  m3 = channels[0];
  m4 = channels[0];

  m1 += channels[1];
  m2 -= channels[1];
  m3 -= channels[1];
  m4 += channels[1];

  m1 += (channels[2] + pid_value) / 1.2;
  m2 -= (channels[2] + pid_value) / 1.2;
  m3 += (channels[2] + pid_value) / 1.2;
  m4 -= (channels[2] + pid_value) / 1.2;

  setMotorSpeed(m1, m2, m3, m4);
}

//void setMotorMove(int m1,int m2,int m3,int m4) {
//  int maxx = abs(m1)>abs(m2)?abs(m1):abs(m2);
//  maxx = maxx>abs(m3)?maxx:abs(m3);
//  maxx = maxx>abs(m4)?maxx:abs(m4);
//
//  if (maxx > 200) {
//    for (int i=0; i<5; i++) {
//      setMotorSpeed(m1*i/5, m2*i/5, m3*i/5, m4*i/5);
//      delay(60);
//    }
//  } else if (maxx>100) {
//    for (int i=0; i<3; i++) {
//      setMotorSpeed(m1*i/3, m2*i/3, m3*i/3, m4*i/3);
//      delay(60);
//    }
//  }
//  setMotorSpeed(m1, m2, m3, m4);
//}

void shiftSpeed() {
  //Set max moving speed
  static int count = 0, prev_state = 0;
  bool flag = false;
  static bool first_time = true;
  if (buttons[7] && (prev_state != 1)) {
    if (count < 2) {
      count += 1;
      flag = true;
      prev_state = 1;
    }
  } else if (buttons[6] && (prev_state != -1)) {
    if (count > 0) {
      count -= 1;
      flag = true;
      prev_state = -1;
    }
  } else if ((!buttons[6]) && (!buttons[7])) {
    prev_state = 0;
  }

  if (flag||first_time) {
//    Serial.println(count);
    switch (count) {
      case 0: {
          max_speed = 100;
          min_speed = -100;
          break;
        }
      case 1: {
          max_speed = 150;
          min_speed = -150;
          break;
        }
      case 2: {
          max_speed = 230;
          min_speed = -230;
          break;
        }
      default: {
          max_speed = 0;
          min_speed = 0;
          break;
        }
    }
    first_time = false;
  }
}

