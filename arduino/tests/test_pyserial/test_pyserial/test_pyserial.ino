#include <Servo.h>

Servo servo;

const byte numChars = 32;
char receivedChars[numChars];   // an array to store the received data

boolean newData = false;

int dataNumber = 0;             // new for this version

void setup() {
    Serial.begin(115200);
    servo.attach(10);
}

void loop() {
  if (Serial.available() > 0) {;
    int num = Serial.parseInt();
    servo.write(num);
    delay(1000);
  }
}
