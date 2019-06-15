#define input A7

int min_value = 10000, max_value = 0;

void setup() {
  Serial.begin(9600);
  pinMode(input, INPUT);
  Serial.println("Start calibrating your stick");
  measure();
}

void loop() {
//  Serial.println(analogRead(input));
}

void measure() {
  int start, val, count = 0;
  int center = 0, min_val = 10000, max_val = 0;
  Serial.println("Now move your stick to the center position, you have 3 seconds to do this");
  start = millis();

  long long int temp = 0;
  while (millis() - start < 3000) {
    temp += analogRead(input);
    count+=1;
  }
  center = temp / count;
  Serial.println("Now move your stick all the way up and down repeatly, you have 5 seconds to do this");
  delay(1000);
  start = millis();
  while (millis() - start < 5000) {
    val = analogRead(input);
    if (val > max_val) {
      max_val = val;
    }
    else if (val < min_val) {
      min_val = val;
    }
  }

  Serial.println("Calibration done, your result: ");
  Serial.print("Center: ");
  Serial.println(center);
  Serial.print("Min value: ");
  Serial.println(min_val);
  Serial.print("Max value: ");
  Serial.println(max_val);
}

