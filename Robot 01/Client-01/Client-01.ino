#include <Servo.h>
#include <SerialCommand.h>

#define ANALOG_CHANNELS 4
#define BUTTON_NUMBERS 17

#define buzz 12
#define res 13

const int motor[2] {3, 4};
const int motorRelay[4] {22, 23, 24, 25};

#define leftArmUp 7
#define leftArmDown 8
#define leftPiston 10
#define leftArmPiston 9

#define rightArmUp 15
#define rightArmDown 14
#define rightPiston 17
#define rightArmPiston 16

#define plateUp 18
#define plateDown 19
#define platePiston 20
#define pushPiston 21

#define SERVO_ATTACH 11
#define IDLE_POS 0
#define RELEASE_POS 0

SerialCommand sCmd;

Servo armLock;

int channels[ANALOG_CHANNELS] = {0};

boolean buttons[BUTTON_NUMBERS] = {false};

byte buttonsBufferCountHigh = 0, buttonsBufferHigh[50] = {0};
byte buttonsBufferCountLow = 0, buttonsBufferLow[50] = {0};

void setup() {
  Serial.begin(9600);
  systemInit();
  buzzer(1, 50); 
  addCommands();
  for(int i=0; i<BUTTON_NUMBERS; i++) {
    processSwitch(i);
  }
  buzzer(2, 50);
}

void(* resetFunc) (void) = 0;

void loop() {
  sCmd.readSerial();
  processSwitchBuffer();
  moveSpinningPlate();
}

void systemInit() {
  pinMode (buzz, OUTPUT);

  for (int i = 0; i < 2; i++) {
    pinMode(motor[i], OUTPUT);
    pinMode(motorRelay[i], OUTPUT);
    pinMode(motorRelay[i+2], OUTPUT);
  }

  pinMode(leftArmUp, OUTPUT);
  pinMode(leftArmDown, OUTPUT);
  pinMode(rightArmUp, OUTPUT);
  pinMode(rightArmDown, OUTPUT);
  pinMode(plateUp, OUTPUT);
  pinMode(plateDown, OUTPUT);

  pinMode(leftPiston, OUTPUT);
  pinMode(leftArmPiston, OUTPUT);
  pinMode(rightPiston, OUTPUT);
  pinMode(rightArmPiston, OUTPUT);
  pinMode(platePiston, OUTPUT);
  pinMode(pushPiston, OUTPUT);

  pinMode(res, OUTPUT);
  digitalWrite(res, HIGH);

  armLock.attach(SERVO_ATTACH);
}

void addCommands() {
  sCmd.addCommand("Ch1", refreshCh1);
  sCmd.addCommand("Ch4", refreshCh4);

  sCmd.addCommand("ToHIGH", buttonToHigh);
  sCmd.addCommand("ToLOW", buttonToLow);
}

