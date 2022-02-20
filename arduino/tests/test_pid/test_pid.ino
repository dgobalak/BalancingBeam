#include <Servo.h>
#include <PID_v1.h>

Servo servo;

const int pingPin = 6; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 7; // Echo Pin of Ultrasonic Sensor
const int servoPin = 10;

const int START_DEG = 0;
const long BEAM_LEN = 50.0;

double Kp=2, Ki=5, Kd=1;
double dist, setPoint;
double angle;

PID pid(&dist, &angle, &setPoint, Kp, Ki, Kd, DIRECT);

void setup() {
  servoSetup(servo, servoPin);  
  
  Serial.begin(9600); // Starting Serial Terminal
  pinMode(pingPin, OUTPUT);    
  pinMode(echoPin, INPUT);

//   Get current distance to ping pong ball
  getCurrDist(dist);
  setPoint = BEAM_LEN / 2;  

  pid.SetMode(AUTOMATIC);
}

void loop() {
  pid.Compute();
  moveServo(servo, (int)angle);
  getCurrDist(dist);
  Serial.println(dist);
  Serial.println("cm");
  Serial.println(angle);
  Serial.println("degrees");
}

void getCurrDist(double &cm) {
   sendPing();
   long duration = duration = pulseIn(echoPin, HIGH);
   cm = microsecondsToCentimeters(duration);
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74.0 / 2.0;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29.0 / 2.0;
}

bool sendPing() {
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);  
  return true;
}

void servoSetup(Servo servo, int pinNum) {
  servo.attach(pinNum);
  servo.write(START_DEG);
}

void moveServo(Servo servo, int angle) {
  servo.write(angle);
  delay(2);
}
