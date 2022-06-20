#include "ultrasonic_handler.h"
#include "lp_filter.h"
#include "servo_handler.h"
#include "pid_control.h"
//#include "mpu6050.h"

#include <stdint.h>
//#include <Wire.h>

const uint8_t ULTRASONIC_ECHO_PIN = 7;
const uint8_t ULTRASONIC_TRIGGER_PIN = 8;

const uint8_t SERVO_PIN = 9;
const uint16_t SERVO_MIN_ANGLE = 0;
const uint16_t SERVO_MAX_ANGLE = 180;

const double LP_FILTER_ALPHA = 0.1;

const long BEAM_LEN = 52.0;

uint16_t angle = INITIAL_ANGLE;

//int16_t acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z;
//double temp;

ServoHandler servo(SERVO_PIN, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE);
UltrasonicHandler ultrasonic(ULTRASONIC_TRIGGER_PIN, ULTRASONIC_ECHO_PIN);
LpFilter lp_filter(LP_FILTER_ALPHA);
PIDController pid(8, 0.02, 4000, 1, BEAM_LEN/2, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE);
//MPU6050 mpu;

void setup() {
    Serial.begin(9600); // Starts the serial communication
//  Wire.begin();
//  mpu.wakeup();
}
void loop() {
    double ball_dist = ultrasonic.get_distance_cm();
    double filtered_dist = lp_filter.get_filtered_value(ball_dist);
    pid.calculate(&angle, &filtered_dist);
    servo.move(angle);
    Serial.println(String(filtered_dist) + " " + String(angle));

//  mpu.read_all_data(&acc_x, &acc_y, &acc_z, &gyro_x, &gyro_y, &gyro_z, &temp);
//  Serial.print("aX = "); Serial.print(mpu.convert_int16_to_str(acc_x));
//  Serial.print(" | aY = "); Serial.print(mpu.convert_int16_to_str(acc_y));
//  Serial.print(" | aZ = "); Serial.print(mpu.convert_int16_to_str(acc_z));
//  Serial.print(" | tmp = "); Serial.print(temp);
//  Serial.print(" | gX = "); Serial.print(mpu.convert_int16_to_str(gyro_x));
//  Serial.print(" | gY = "); Serial.print(mpu.convert_int16_to_str(gyro_y));
//  Serial.print(" | gZ = "); Serial.print(mpu.convert_int16_to_str(gyro_z));
//  Serial.println();
//  delay(1000);
}
