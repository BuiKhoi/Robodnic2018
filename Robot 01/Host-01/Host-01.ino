#include <SimpleKalmanFilter.h>

#define ANALOG_CHANNELS 4
#define BUTTON_NUMBERS 13
int MINIMUM_VALUE = -200;
int MAXIMUM_VALUE = 200;
#define DIFFERENTAL 5

#define ch1 A4
#define ch2 A6
#define ch3 A7
#define ch4 A5

#define btn0 2
#define btn1 3
#define btn2 8
#define btn3 4
#define btn4 6
#define btn5 7
#define btn6 13
#define btn7 9
#define btn8 10
#define btn9 11
#define btn10 12
#define btn11 A2
#define btn12 A3

#define buzz A0

SimpleKalmanFilter filterCh1(2, 2, 0.01);
SimpleKalmanFilter filterCh2(2, 2, 0.01);
SimpleKalmanFilter filterCh3(2, 2, 0.01);
SimpleKalmanFilter filterCh4(2, 2, 0.01);

int channels[ANALOG_CHANNELS] = {0};
int prev_channels[ANALOG_CHANNELS] = {0};

byte buttonsPins[BUTTON_NUMBERS] = {btn0, btn1, btn2, btn3, btn4, btn5, btn6, btn7, btn8, btn9, btn10, btn11, btn12};
boolean buttons[BUTTON_NUMBERS] = {false};

void(* resetFunc) (void) = 0;

void setup() {
  Serial.begin(9600);
  IOInit();

  int start = millis();
  buzzer(1, 200);
//  while (digitalRead(btn0) == LOW) {
//    if (millis() - start > 1000) {
//      buzzer(1, 200);
//      start = millis();
//    }
//    delay(50);
//  }
//  buzzer(3, 200);
}

void loop() {
  checkMaxSpeed();
  
  channels[0] = decodeValue((int)filterCh1.updateEstimate(analogRead(ch1)), 500, 34, 933);
  ignoreDifferental(0, channels[0]);
  channels[1] = decodeValue((int)filterCh2.updateEstimate(analogRead(ch2)), 515, 52, 990);
  ignoreDifferental(1, channels[1]);
  channels[2] = decodeValue((int)filterCh3.updateEstimate(analogRead(ch3)), 514, 75, 981);
  ignoreDifferental(2, channels[2]);
  channels[3] = decodeValue((int)filterCh4.updateEstimate(analogRead(ch4)), 502, 62, 959);
  ignoreDifferental(3, channels[3]);

  for (int i = 0; i < BUTTON_NUMBERS; i++) {
    if (digitalRead(buttonsPins[i]) != buttons[i]) {
      buttons[i] = !buttons[i];
      if (buttons[i]) {
        Serial.print("ToHIGH ");
      } else {
        Serial.print("ToLOW ");
      }
      Serial.println(i);
    }
  }
  
  if (buttons[10]) {
    delay(500);
    resetFunc();
  }

  delay(20);
}

void IOInit() {
  pinMode(ch1, INPUT);
  pinMode(ch2, INPUT);
  pinMode(ch3, INPUT);
  pinMode(ch4, INPUT);
  pinMode(buzz, OUTPUT);

  for (int i = 0; i < BUTTON_NUMBERS; i++) {
    pinMode(buttonsPins[i], INPUT);
  }
}

int decodeValue(int val, int center, int min_val, int max_val) {
  val = constrain(val, min_val, max_val);
  if (val >= center) {
    return maps(val, center, max_val, 0, MAXIMUM_VALUE);
  } else if (val < center) {
    return maps(val, min_val, center, MINIMUM_VALUE, 0);
  }
}

int maps(int input, int Ain, int Aout, int Bin, int Bout) {
  float temp = input - Ain;
  temp /= (Aout - Ain);
  temp *= (Bout - Bin);
  temp += Bin;
  return temp;
}

void ignoreDifferental(int channel, int val) {
  if (abs(val - prev_channels[channel]) > DIFFERENTAL) {
    prev_channels[channel] = val;
    switch (channel) {
      case 0: {
          Serial.print("Ch1 ");
          break;
        }
      case 1: {
          Serial.print("Ch2 ");
          break;
        }
      case 2: {
          Serial.print("Ch3 ");
          break;
        }
      case 3: {
          Serial.print("Ch4 ");
          break;
        }
    }
    Serial.println(val);
  }
}

void checkMaxSpeed() {
  if (buttons[12]) {
    MINIMUM_VALUE = -255;
    MAXIMUM_VALUE = 255;
  } else {
    MINIMUM_VALUE = -200;
    MAXIMUM_VALUE = 200;
  }
}

void buzzer(int count, int time) {
  for (int i = 0; i < count; i++) {
    digitalWrite(buzz, HIGH);
    delay(time);
    digitalWrite(buzz, LOW);
    delay(time / 2);
  }
}
