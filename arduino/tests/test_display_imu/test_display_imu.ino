#include <font6x8.h>
#include <nano_engine.h>
#include <nano_gfx.h>
#include <nano_gfx_types.h>
#include <sprite_pool.h>
#include <ssd1306.h>
#include <ssd1306_16bit.h>
#include <ssd1306_1bit.h>
#include <ssd1306_8bit.h>
#include <ssd1306_console.h>
#include <ssd1306_fonts.h>
#include <ssd1306_generic.h>
#include <ssd1306_uart.h>

#include "ssd1306.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "nano_gfx.h"

Adafruit_MPU6050 mpu;

static void introScreen()
{
    ssd1306_setFixedFont(ssd1306xled_font8x16);
    ssd1306_clearScreen();
    ssd1306_printFixed(0,  8, "USELESS BALANZ", STYLE_NORMAL);
    delay(3500);
}

static void setUpAccel()
{
  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");
  delay(100);
}

static void getAccel()
{
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);


      ssd1306_printFixed(50, 8, "    ", STYLE_NORMAL);
      ssd1306_printFixed(100, 40, "  ", STYLE_NORMAL);
      //ssd1306_clearScreen();
      ssd1306_printFixed(5, 8, "Temp: ", STYLE_NORMAL);
      ssd1306_printFixed(5, 40, "Amount Tilt:", STYLE_NORMAL);

      // get temperature
      char myTemp[20];
      dtostrf(temp.temperature, 2, 2, myTemp);

      // get angle
      uint8_t myAngle = abs((atan2(a.acceleration.x, a.acceleration.y) * 180 / PI) - 90);
      if (myAngle >= 10)
        ssd1306_printFixed(5, 40, "             ", STYLE_NORMAL);
      char angle[20];
      dtostrf(myAngle, 2, 0, angle);
      
      ssd1306_printFixed(50, 8, myTemp, STYLE_NORMAL);

      ssd1306_printFixed(100, 40, angle, STYLE_NORMAL);
      
      delay(10);
  
}

unsigned long prevTime = 0;
unsigned long currentTime = millis();

void setup() {
  Serial.begin(9600);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  setUpAccel();
  
  ssd1306_setFixedFont(ssd1306xled_font8x16);
  ssd1306_128x64_i2c_init();
  ssd1306_clearScreen();

  delay(1000);

  ssd1306_drawLine(0,0, ssd1306_displayWidth() -1, 0);

  introScreen();

  ssd1306_clearScreen();
  
}

void loop() {
  
  delay(500);
  //ssd1306_clearScreen();

  getAccel();

}
