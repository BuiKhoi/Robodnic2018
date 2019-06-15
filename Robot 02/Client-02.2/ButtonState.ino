void getButtonState() {
  //Scan all button state for new events
  ps2x.read_gamepad(false, 0);
  if (true) {
    //Analog read
    channels[0] = map(ps2x.Analog(PSS_LY), 256, 0, min_speed, max_speed);
    channels[1] = map(ps2x.Analog(PSS_LX), 0, 256, min_speed, max_speed);
    channels[2] = map(ps2x.Analog(PSS_RX), 0, 256, min_speed, max_speed);

    //Moving buttons
    bool temp = ps2x.Button(PSB_L1);
    if (temp != buttons[1]) {
      buttons[1] = temp;
      processSwitch(1);
    }

    //Arm buttons
    temp = ps2x.Button(PSB_R2);
    if (temp != buttons[2]) {
      buttons[2] = temp;
      processSwitch(2);
    }

    temp = ps2x.Button(PSB_R1);
    if (temp != buttons[3]) {
      buttons[3] = temp;
      processSwitch(3);
    }

    temp = ps2x.Button(PSB_SQUARE);
    if (temp != buttons[10]) {
      buttons[10] = temp;
      if (temp) {
        processSwitch(10);
      }
    }

    temp = ps2x.Button(PSB_CIRCLE);
    if (temp != buttons[11]) {
      buttons[11] = temp;
      if (temp) {
        processSwitch(11);
      }
    }

    //Hand buttons
    temp = ps2x.Button(PSB_TRIANGLE);
    if (temp != buttons[8]) {
      buttons[8] = temp;
      if (temp) {
        processSwitch(8);
      }
    }

    temp = ps2x.Button(PSB_CROSS);
    if (temp != buttons[9]) {
      buttons[9] = temp;
      if (temp) {
        processSwitch(9);
      }
    }

    temp = ps2x.Button(PSB_L2);
    if (temp != buttons[0]) {
      buttons[0] = temp;
      if (temp) {
        processSwitch(0);
      }
    }

    //Speed Buttons
    temp = ps2x.Button(PSB_PAD_UP);
    if (temp != buttons[4]) {
      if (temp) {
        channels[0] = 100;
      } else {
        channels[0] = 0;
      }
    }

    temp = ps2x.Button(PSB_PAD_DOWN);
    if (temp != buttons[5]) {
      if (temp) {
        channels[0] = -100;
      } else {
        channels[0] = 0;
      }
    }

    temp = ps2x.Button(PSB_PAD_LEFT);
    if (temp != buttons[6]) {
      buttons[6] = temp;
    }

    temp = ps2x.Button(PSB_PAD_RIGHT);
    if (temp != buttons[7]) {
      buttons[7] = temp;
    }

    //Additional buttons
    if (ps2x.Button(PSB_START)) {
      int start = millis();
      while (ps2x.Button(PSB_START)) {
        ps2x.read_gamepad(false, 0);
        if (millis() - start > 500) {
          setMotorSpeed(100, 100, 100, 100);
          //          Serial.println("Prekick");
          delay(200);
          setMotorSpeed(170, 170, 170, 170);
          //          Serial.println("Prekick");
          delay(200);

          while (ps2x.Button(PSB_START)) {
            ps2x.read_gamepad(false, 0);
            setMotorSpeed(255, 255, 255, 255);
            //            Serial.println("Kickingggg");
          }
          break;
        }
      }
    }
  }
}


