#include <HMC5883L.h>
#include <SimpleKalmanFilter.h>
#include <SerialCommand.h>

#define ANALOG_CHANNELS 4
#define BUTTON_NUMBERS 14

#define buzz 18
#define PS2_DAT        10  //14    
#define PS2_CMD        11  //15
#define PS2_SEL        13  //16
#define PS2_CLK        12  //17

const int motor1[2] = {9, 8};
const int motor2[2] = {3, 2};
const int motor3[2] = {5, 4};
const int motor4[2] = {7, 6};

#define upperHand 16
#define lowerHand 14
#define moveArm  17
#define pushArm   15

#define pullArmUp   20
#define pullArmDown 21
#define pulloutArm  19

#define kP 0
#define kI 0
#define kD 0

SerialCommand sCmd;

SimpleKalmanFilter filter(1, 1, 0.001);

HMC5883L compass;
int comp_angle;

int channels[ANALOG_CHANNELS] = {0};

boolean buttons[BUTTON_NUMBERS] = {false};

void(* resetFunc) (void) = 0;

byte buttonsBufferCountHigh = 0, buttonsBufferHigh[50] = {0};
byte buttonsBufferCountLow  = 0, buttonsBufferLow[50]  = {0};

void setup() {
  systemInit();
  buzzer(1, 200);
  addCommands();
  for(int i=0; i<BUTTON_NUMBERS; i++) {
    processSwitch(i);
  }
  buzzer(2, 200);
}

void loop() {
  sCmd.readSerial();
  moveRobot();
  processSwitchBuffer();

//  setMotorSpeed(0, 0, 0, 0);
}

void systemInit() {
  Serial.begin(9600);
  pinMode (buzz, OUTPUT);

  for (int i = 0; i < 2; i++) {
    pinMode(motor1[i], OUTPUT);
    pinMode(motor2[i], OUTPUT);
    pinMode(motor3[i], OUTPUT);
    pinMode(motor4[i], OUTPUT);
  }

  pinMode(upperHand, OUTPUT);
  pinMode(lowerHand, OUTPUT);
  pinMode(moveArm, OUTPUT);
  pinMode(pushArm, OUTPUT);

  pinMode(pullArmUp, OUTPUT);
  pinMode(pullArmDown, OUTPUT);
  pinMode(pulloutArm, OUTPUT);

//  while (!compass.begin()) {
//
//  }
//
//  compass.setRange(HMC5883L_RANGE_1_3GA);
//  compass.setMeasurementMode(HMC5883L_CONTINOUS);
//  compass.setDataRate(HMC5883L_DATARATE_15HZ);
//  compass.setSamples(HMC5883L_SAMPLES_1);
//  comp_angle = filter.updateEstimate(compass.readRaw().XAxis);
}

void addCommands() {
  sCmd.addCommand("Ch1", refreshCh1);
  sCmd.addCommand("Ch2", refreshCh2);
  sCmd.addCommand("Ch3", refreshCh3);
  sCmd.addCommand("Ch4", refreshCh4);

  sCmd.addCommand("ToHIGH", buttonToHigh);
  sCmd.addCommand("ToLOW", buttonToLow);
}
