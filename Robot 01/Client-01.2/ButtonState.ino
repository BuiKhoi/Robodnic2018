void getButtonState() {
  ps2x.read_gamepad(false, 0);
  //Moving buttons
  boolean temp = ps2x.Button(PSB_PAD_UP);
  if (temp != buttons[4]) {
    buttons[4] = temp;
    buttonStateChange = true;
    if (!temp) {
      buttons[4] = buttons[5] = buttons[10] = buttons[11] = false;
    }
  }

  temp = ps2x.Button(PSB_PAD_DOWN);
  if (temp != buttons[5]) {
    buttons[5] = temp;
    buttonStateChange = true;
    if (!temp) {
      buttons[4] = buttons[5] = buttons[10] = buttons[11] = false;
    }
  }

  temp = ps2x.Button(PSB_SQUARE);
  if (temp != buttons[10]) {
    buttons[10] = temp;
    buttonStateChange = true;
    if (buttons[4] || buttons[5]) {
      if (!temp) {
        buttons[4] = buttons[5] = buttons[10] = buttons[11] = false;
      }
    }
  }

  temp = ps2x.Button(PSB_CIRCLE);
  if (temp != buttons[11]) {
    buttons[11] = temp;
    buttonStateChange = true;
    if (buttons[4] || buttons[5]) {
      if (!temp) {
        buttons[4] = buttons[5] = buttons[10] = buttons[11] = false;
      }
    }
  }

  //Arm buttons
  temp = ps2x.Button(PSB_L1);
  if (temp != buttons[1]) {
    buttons[1] = temp;
    processSwitch(1);
  }

  temp = ps2x.Button(PSB_L2);
  if (temp != buttons[0]) {
    buttons[0] = temp;
    processSwitch(0);
  }

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

  //Hand buttons
  int channel = ps2x.Analog(PSS_RX);
  if (channel > 200) {
    temp = true;
  } else temp = false;
  if (temp != buttons[7]) {
    buttons[7] = temp;
    if (temp) {
      processSwitch(7);
    }
    temp = false;
  }

  channel = ps2x.Analog(PSS_LX);
  if (channel < 30) {
    temp = true;
  } else temp = false;
  if (temp != buttons[6]) {
    buttons[6] = temp;
    if (temp) {
      processSwitch(6);
    }
  }

  //Plate buttons
  temp = ps2x.Button(PSB_SELECT);
  if (temp != buttons[12]) {
    buttons[12] = temp;
    if (temp) {
      processSwitch(12);
    }
  }

  temp = ps2x.Button(PSB_R3);
  if (temp != buttons[13]) {
    buttons[13] = temp;
    if (temp) {
      processSwitch(13);
    }
  }

  temp = ps2x.Button(PSB_TRIANGLE);
  if (temp != buttons[8]) {
    buttons[8] = temp;
    if (temp) {
      setPlateMove(1);
    } else {
      setPlateMove(0);
    }
  }

  temp = ps2x.Button(PSB_CROSS);
  if (temp != buttons[9]) {
    buttons[9] = temp;
    if (temp) {
      setPlateMove(-1);
    } else {
      setPlateMove(0);
    }
  }

  //Additional buttons
  if (ps2x.Button(PSB_START)) {
    armLock.write(RELEASE_POS);
  }
}

