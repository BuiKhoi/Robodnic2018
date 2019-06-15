void refreshCh1() {
  char *arg;
  arg = sCmd.next();
  int value = atoi(arg);
  channels[0] = (int) value;
  sCmd.clearBuffer();
}

void refreshCh2() {
  char *arg;
  arg = sCmd.next();
  int value = atoi(arg);
  channels[1] = (int) value;
  sCmd.clearBuffer();
}

void refreshCh3() {
  char *arg;
  arg = sCmd.next();
  int value = atoi(arg);
  channels[2] = (int) value;
  sCmd.clearBuffer();
}

void refreshCh4() {
  char *arg;
  arg = sCmd.next();
  int value = atoi(arg);
  channels[3] = (int) value;
  sCmd.clearBuffer();
}

void buttonToHigh() {
  char *arg;
  arg = sCmd.next();
  int i = atoi(arg);
  if (i < BUTTON_NUMBERS && buttonsBufferCountHigh < 50) {
    buttons[i] = true;
    buttonsBufferHigh[buttonsBufferCountHigh] = i;
  }
  sCmd.clearBuffer();
  buzzer(1, 50);
}

void buttonToLow() {
  char *arg;
  arg = sCmd.next();
  int i = atoi(arg);
  if (i < BUTTON_NUMBERS && buttonsBufferCountLow < 50) {
    buttons[i] = true;
    buttonsBufferLow[buttonsBufferCountLow] = i;
  }
  sCmd.clearBuffer();
  buzzer(1, 50);
}

