#include <Wire.h>
#include <HMC5883L.h>

HMC5883L compass;
float first_angle = 0, heading = 0;
Vector norm;
void setup() {
  Serial.begin(9600);
  Serial.println("Initialize HMC5883L");
  while (!compass.begin())
  {
    Serial.println("Could not find a valid HMC5883L sensor, check wiring!");
    delay(500);
  }
  compass.setRange(HMC5883L_RANGE_1_3GA);
  compass.setMeasurementMode(HMC5883L_CONTINOUS);
  compass.setDataRate(HMC5883L_DATARATE_30HZ);
  compass.setSamples(HMC5883L_SAMPLES_8);
  compass.setOffset(134, -390);
  first_angle = getHeading();
  Serial.print("System started  ");
  Serial.println(first_angle);
}

void loop() {
  Serial.println(getDifferental());
}

float getDifferental() {
  float differental = getHeading() - first_angle;
  if (abs(differental) > PI) {
    int temp = differental / abs(differental);
    differental = 2 * PI - abs(differental);
    differental *= temp;
  }
  return differental;
}

float getHeading() {
  Vector norm = compass.readNormalize();
  float heading = atan2(norm.YAxis, norm.XAxis);
  float declinationAngle = (-1.0 + (12.0 / 60.0)) / (180 / M_PI);
  heading += declinationAngle;
  if (heading < 0)
  {
    heading += 2 * PI;
  }

  if (heading > 2 * PI)
  {
    heading -= 2 * PI;
  }
  return heading;
}

