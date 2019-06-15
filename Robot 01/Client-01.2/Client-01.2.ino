#include <Servo.h>
#include <PS2X_lib.h>

#define buzz 37

#define shiftSpeed01 7
const int motorRelay[4] {23, 25, 29, 27};

#define leftArmUp 3
#define leftArmDown 2
#define leftPiston 5

#define rightArmUp 14
#define rightArmDown 17
#define rightPiston 15

#define plateCW 19
#define plateCCW 4
#define platePiston 20
#define pushPiston 21

#define SERVO_ATTACH 8
#define IDLE_POS 0
#define RELEASE_POS 180

#define PS2_DAT 13  
#define PS2_CMD 11
#define PS2_SEL 10
#define PS2_CLK 12

#define pressures   false
#define rumble      false

#define BUTTON_NUMBERS 14

PS2X ps2x;
Servo armLock;

boolean buttons[BUTTON_NUMBERS]  = {false};
boolean buttonStateChange = false;

void setup() {
  int error = 0;
  byte type = 0;
  byte vibrate = 0;
  Serial.begin(9600);
  systemInit();
  buzzer(1, 50);
  for (int i = 0; i < BUTTON_NUMBERS; i++) {
    processSwitch(i);
  }

  delay(300);
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  while (error != 0);
  type = ps2x.readType();
  while (type != 1);
  ps2x.read_gamepad(false, vibrate);
  
  buzzer(2, 50);
  shiftSpeed(1);
  Serial.println("System Started");
}

void loop() {
  getButtonState();
  moveRobot();
}

void systemInit() {
  pinMode (buzz, OUTPUT);
  pinMode(shiftSpeed01, OUTPUT);
  for (int i = 0; i < 4; i++) {
    pinMode(motorRelay[i], OUTPUT);
  }

  pinMode(leftArmUp, OUTPUT);
  pinMode(leftArmDown, OUTPUT);
  pinMode(rightArmUp, OUTPUT);
  pinMode(rightArmDown, OUTPUT);
  pinMode(plateCW, OUTPUT);
  pinMode(plateCCW, OUTPUT);

  pinMode(leftPiston, OUTPUT);
  pinMode(rightPiston, OUTPUT);
  pinMode(platePiston, OUTPUT);
  pinMode(pushPiston, OUTPUT);
  setPlateMove(0);
  armLock.attach(SERVO_ATTACH);
  armLock.write(IDLE_POS);
}
