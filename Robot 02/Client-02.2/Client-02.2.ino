#include <HMC5883L.h>
#include <SimpleKalmanFilter.h>
#include <Servo.h>
#include <PS2X_lib.h>

#define ANALOG_CHANNELS 3
#define BUTTON_NUMBERS 14

int max_speed = 100;
int min_speed = -100;

#define buzz 26
#define PS2_DAT 13
#define PS2_CMD 11
#define PS2_SEL 10
#define PS2_CLK 12

const int motor1[2] = {6, 7};
const int motor2[2] = {3, 2};
const int motor3[2] = {9, 8};
const int motor4[2] = {5, 4};

#define upperHand 15
#define lowerHand 16
#define moveArm   17
#define pushArm   14

#define pullArmUp   18
#define pullArmDown 21
#define highHand    20
#define pulloutArm  19

#define pressures   false
#define rumble      false

#define kP 0/*Value deleted*/
#define kI 0/*Value deleted*/
#define kD 0/*Value deleted*/

PS2X ps2x;
SimpleKalmanFilter filter(1, 1, 0.001);

HMC5883L compass;
float first_angle = 0;

int error = 0;
byte type = 0;
byte vibrate = 0;

boolean buttons[BUTTON_NUMBERS]  = {false};
int channels[ANALOG_CHANNELS] = {0};

void setup() {
  //Setup Serial debugger and initalize IO components
  Serial.begin(9600);
  systemInit();
  buzzer(1, 50);
  for (int i = 0; i < BUTTON_NUMBERS; i++) {
    processSwitch(i);
  }
  //Start PS2
  delay(300);
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  while (error != 0);
  type = ps2x.readType();
  while (type != 1);
  //Get setpoint for PID computing
  first_angle = getHeading();
  buzzer(2, 50);
  Serial.println("System started");
  //Finish setup
}

//void(* resetFunc) (void) = 0;

void loop() {
  getButtonState();
  shiftSpeed();
  moveRobot();

  //  setMotorSpeed(0, 0 , 0 , 0);
}

void systemInit() {
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
  pinMode(highHand, OUTPUT);

  pinMode(pullArmUp, OUTPUT);
  pinMode(pullArmDown, OUTPUT);
  pinMode(pulloutArm, OUTPUT);

  while (!compass.begin());
  compass.setRange(HMC5883L_RANGE_1_3GA);
  compass.setMeasurementMode(HMC5883L_CONTINOUS);
  compass.setDataRate(HMC5883L_DATARATE_30HZ);
  compass.setSamples(HMC5883L_SAMPLES_8);
  compass.setOffset(134, -390);
}
