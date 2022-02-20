#include <Servo.h>
#include <PID_v1.h>

Servo servo;

const int pingPin = 6; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 7; // Echo Pin of Ultrasonic Sensor
const int servoPin = 10;

const int START_DEG = 0;
const long BEAM_LEN = 52.0;

const long MIN_TARGET_CHANGE = 5; // cm

double Kp = 8, Ki = 0.02, Kd = 4000;
double dist, setPoint;
double angle;

bool calibrated = false;

PID pid(&dist, &angle, &setPoint, Kp, Ki, Kd, DIRECT);

void setup() {
  servoSetup(servo, servoPin);  

//  Ultrasonic setup
  Serial.begin(115200);
  pinMode(pingPin, OUTPUT);    
  pinMode(echoPin, INPUT);

//   Get current distance to ping pong ball
  getCurrDist(dist);
  setPoint = BEAM_LEN;  

  pid.SetMode(AUTOMATIC);
}

void loop() {
//  while (!calibrated) {
//    if (Serial.available() > 0) {;
//      int num = Serial.parseInt();
//      setPoint = (double)num;
//      delay(100);
//      calibrated  = true;
//    }
//  }

  if (dist < 20) {
    moveServo(servo, 180);
  }

  calibrated = true;
  pid.Compute();
  moveServo(servo, (int)angle);
  getCurrDist(dist);
}

void getCurrDist(double &cm) {
   sendPing();
   long duration = duration = pulseIn(echoPin, HIGH);
   cm = microsecondsToCentimeters(duration);
}

bool sendPing() {
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);  
  return true;
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74.0 / 2.0;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29.0 / 2.0;
}

void servoSetup(Servo servo, int pinNum) {
  servo.attach(pinNum);
  servo.write(START_DEG);
}

void moveServo(Servo servo, int angle) {
  servo.write(angle);
  delay(2);
}
