#include <math.h>
#include "kalman.h"


long double measurement;
float start, curr;
Kalman filter(0.0, 0.5, 10, 1, 1, 0.5, 2, 0.5);

void setup() {
  Serial.begin(115200);
  Serial.println("Starting Tests...");
  measurement = 0.0;
  start = millis();
}

void loop() {
  long val = random(-1, 1);
  long double f_result = filter.run(measurement);
  Serial.println((double)f_result);

  long double dt = (millis() - start) * 1000;
  measurement = measurement + dt * 1;
}