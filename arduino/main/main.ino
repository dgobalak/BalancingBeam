#include <Servo.h>

Servo leftServo, rightServo;

//int leftPos = 0, rightPos = 0;
const int START_DEG = 0;

void setup() {
  servoSetup(leftServo, 12);
  servoSetup(rightServo, 10);
}

void loop() {
  sweepServo(leftServo);
  delay(1000);
  sweepServo(rightServo);
  delay(1000);
}

void servoSetup(Servo servo, int pinNum) {
  servo.attach(pinNum);
  servo.write(START_DEG);
}

void sweepServo(Servo servo) {
  int pos = 10;
  for (pos = 10; pos <= 170; pos += 1) {
    servo.write(pos);        
    delay(2);                      
  }
  for (pos = 170; pos >= 10; pos -= 1) {
    servo.write(pos);
    delay(2);                      
  }
}
