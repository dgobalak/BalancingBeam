#include "mpu6050.h"

#include <Wire.h>
#include <stdint.h>

MPU6050::MPU6050() {
    this->device_addr = MPU6050_DEFAULT_ADDRESS;
}

MPU6050::MPU6050(uint8_t device_addr) {
    if (device_addr != MPU6050_ADDRESS_AD0_HIGH && device_addr != MPU6050_ADDRESS_AD0_LOW) {
        device_addr = MPU6050_DEFAULT_ADDRESS;
    }
    this->device_addr = device_addr;
}

void MPU6050::wakeup() {
    Wire.beginTransmission(this->device_addr);
    Wire.write(MPU6050_REG_PWR_MGMT_1);
    Wire.write(0);
    Wire.endTransmission(true);
}

bool MPU6050::read_register(uint8_t reg, uint8_t *data) {
    Wire.beginTransmission(this->device_addr);
    Wire.write(reg);
    Wire.endTransmission(false);
    Wire.requestFrom(this->device_addr, 1, true);
    if (Wire.available() == 1) {
        *data = Wire.read();
        return true;
    }
    return false;
}

bool MPU6050::read_registers(uint8_t reg, int8_t *data, uint8_t num_bytes) {
    Wire.beginTransmission(this->device_addr);
    Wire.write(reg);
    Wire.endTransmission(false);
    Wire.requestFrom(this->device_addr, num_bytes, true);
    if (Wire.available() == num_bytes) {
        for (uint8_t i = 0; i < num_bytes; i++) {
            data[i] = Wire.read();
        }
        return true;
    }
    return false;
}

bool MPU6050::write_register(uint8_t reg, uint8_t data) {
    Wire.beginTransmission(this->device_addr);
    Wire.write(reg);
    Wire.write(data);
    Wire.endTransmission(true);
    return true;
}

char* MPU6050::convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
    sprintf(this->tmp_str, "%6d", i);
    return this->tmp_str;
}

bool MPU6050::read_all_data(int16_t *acc_x, int16_t *acc_y, int16_t *acc_z, int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z, double *temp) {
    int8_t data[14];
    if ( this->read_registers(MPU6050_REG_ACCEL_XOUT_H, data, 14) ) {
        *acc_x = (int16_t)((data[0] << 8) | data[1]);
        *acc_y = (int16_t)((data[2] << 8) | data[3]);
        *acc_z = (int16_t)((data[4] << 8) | data[5]);
        *gyro_x = (int16_t)((data[6] << 8) | data[7]);
        *gyro_y = (int16_t)((data[8] << 8) | data[9]);
        *gyro_z = (int16_t)((data[10] << 8) | data[11]);
        *temp = ( (int16_t)((data[12] << 8) | data[13]) / 340.0f + 36.53f );        
        return true;
    }
    return false;
}
