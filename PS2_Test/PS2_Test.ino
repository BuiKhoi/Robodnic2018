#include <PS2X_lib.h>

int PS2_DAT = 13; //14
int PS2_CMD = 11; //15
int PS2_SEL = 10; //16
int PS2_CLK = 12; //17`

#define pressures   false
#define rumble      false

boolean buttons[14]  = {false};

PS2X ps2x;

void setup() {
  int error = 0;
  byte type = 0;
  byte vibrate = 0;
  Serial.begin(9600);
  delay(300);

  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  bool found = true;
  if (error != 0) {
    found = false;
    Serial.println("Wiring problem, trying scanning...");
    for (int a = 10; a < 14; a++) {
      PS2_DAT = a;
      for (int b = 10; b < 14; b++) {
        if (b == a) continue;
        PS2_CMD = b;
        for (int c = 10; c < 14; c++) {
          if (c == a || c == b) continue;
          PS2_SEL = c;
          for (int d = 10; d < 14; d++) {
            if (d == a || d == b || d == c) continue;
            PS2_CLK = d;
            error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
            if (error == 0) {
              Serial.print("New wire order: ");
              Serial.print(PS2_DAT);
              Serial.print("  ");
              Serial.print(PS2_CMD);
              Serial.print("  ");
              Serial.print(PS2_SEL);
              Serial.print("  ");
              Serial.println(PS2_CLK);
              found = true;
              break;
            }
          }
        }
      }
    }
  }

  if (!found) Serial.println("Wiring could not complete, check and try again");

  type = ps2x.readType();
  while (type != 1);


  Serial.println("System Initalized");
}

void loop() {
  getButtonState();
}

void getButtonState() {
  ps2x.read_gamepad(false, 0);
  if (ps2x.NewButtonState()) {
    boolean temp = ps2x.Button(PSB_PAD_UP);
    //Moving buttons
    if (temp != buttons[4]) {
      buttons[4] = temp;
      Serial.println("Button 4");
    }

    temp = ps2x.Button(PSB_PAD_DOWN);
    if (temp != buttons[5]) {
      buttons[5] = temp;
      Serial.println("Button 5");
    }

    temp = ps2x.Button(PSB_SQUARE);
    if (temp != buttons[10]) {
      buttons[10] = temp;
      Serial.println("Button 10");
    }

    temp = ps2x.Button(PSB_CIRCLE);
    if (temp != buttons[11]) {
      buttons[11] = temp;
      Serial.println("Button 11");
    }

    //Arm buttons
    temp = ps2x.Button(PSB_L2);
    if (temp != buttons[0]) {
      buttons[0] = temp;
      Serial.println("Button 0");
    }

    temp = ps2x.Button(PSB_L1);
    if (temp != buttons[1]) {
      buttons[1] = temp;
      Serial.println("Button 1");
    }

    temp = ps2x.Button(PSB_R2);
    if (temp != buttons[2]) {
      buttons[2] = temp;
      Serial.println("Button 2");
    }

    temp = ps2x.Button(PSB_R1);
    if (temp != buttons[3]) {
      buttons[3] = temp;
      Serial.println("Button 3");
    }

    temp = ps2x.Button(PSB_PAD_LEFT);
    if (temp != buttons[6]) {
      buttons[6] = temp;
      Serial.println("Button 6");
    }

    temp = ps2x.Button(PSB_PAD_RIGHT);
    if (temp != buttons[7]) {
      buttons[7] = temp;
      Serial.println("Button 7");
    }

    //Hand buttons
    temp = ps2x.Button(PSB_TRIANGLE);
    if (temp != buttons[8]) {
      buttons[8] = temp;
      Serial.println("Button 8");
    }

    temp = ps2x.Button(PSB_CROSS);
    if (temp != buttons[9]) {
      buttons[9] = temp;
      Serial.println("Button 9");
    }

    //Plate buttons
    temp = ps2x.Button(PSB_L3);
    if (temp != buttons[12]) {
      buttons[12] = temp;
      Serial.println("Button 12");
    }

    temp = ps2x.Button(PSB_R3);
    if (temp != buttons[13]) {
      buttons[13] = temp;
      Serial.println("Button 13");
      process(13);
    }

    //Additional buttons
    if (ps2x.Button(PSB_START)) {
      Serial.println("Request system reset");
    }
  }
}

void process(int a) {
  if (a == 13) {
    if (buttons[13]) {
      static bool count = false;
      if ((count = !count)) {
        Serial.println("Led illuminating");
      } else {
        Serial.println("Led off");
      }
    }
  }
}

