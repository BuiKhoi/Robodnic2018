#include <SimpleKalmanFilter.h>

#define ANALOG_CHANNELS 4
#define BUTTON_NUMBERS 12
#define MINIMUM_VALUE -100
#define MAXIMUM_VALUE 100

#define ch1 A1
#define ch2 A2
#define ch3 A3
#define ch4 A4

#define btn1 2
#define btn2 3
#define btn3 4
#define btn4 5
#define btn5 6
#define btn6 7
#define btn7 8
#define btn8 9
#define btn9 10
#define btn10 11
#define btn11 12
#define btn12 13

SimpleKalmanFilter filterCh1(2, 2, 0.01);
SimpleKalmanFilter filterCh2(2, 2, 0.01);
SimpleKalmanFilter filterCh3(2, 2, 0.01);
SimpleKalmanFilter filterCh4(2, 2, 0.01);

byte channels[ANALOG_CHANNELS] = {0};

byte buttonsPins[BUTTON_NUMBERS] = {btn1, btn2, btn3, btn4, btn5, btn6, btn7, btn8, btn9, btn10, btn11, btn12};
boolean buttons[BUTTON_NUMBERS] = {false};

void setup() {
  Serial.begin(9600);
  IOInit();
}

void loop() {
  channels[1] = decodeValue(filterCh1.updateEstimate(analogRead(ch1)), 0, 110, 841);
  Serial.print("Ch1 "); Serial.println(channels[1]);
  channels[2] = decodeValue(filterCh2.updateEstimate(analogRead(ch2)), 0, 147, 882);
  Serial.print("Ch2 "); Serial.println(channels[2]);
  channels[3] = decodeValue(filterCh3.updateEstimate(analogRead(ch3)), 1, 109, 843);
  Serial.print("Ch3 "); Serial.println(channels[3]);
  channels[4] = decodeValue(filterCh4.updateEstimate(analogRead(ch4)), 0, 123, 857);
  Serial.print("Ch4 "); Serial.println(channels[4]);

  for (int i = 0; i < BUTTON_NUMBERS; i++) {
    if (digitalRead(buttonsPins[i]) != buttons[i]) {
      buttons[i] = !buttons[i];
      Serial.print("BtnChgn ");
      Serial.println(i);
    }
  }

  delay(50);
}

void IOInit() {
  pinMode(ch1, INPUT);
  pinMode(ch2, INPUT);
  pinMode(ch3, INPUT);
  pinMode(ch4, INPUT);

  for (int i = 0; i < BUTTON_NUMBERS; i++) {
    pinMode(buttonsPins[i], INPUT);
  }
}

int decodeValue(int val, int center, int min_val, int max_val) {
  val = constrain(val, min_val, max_val);
  if (val >= center) {
    return map(val, center, max_val, 0, MAXIMUM_VALUE);
  } else if (val < center) {
    return map(val, min_val, center, MINIMUM_VALUE, 0);
  }
}

