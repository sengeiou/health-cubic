#ifndef DEVICE_H
#define DEVICE_H

#include <TFT_eSPI.h>
#include "Arduino.h"
#include "driver/rgb_led.h"
#include "driver/sd_card.h"
#include "driver/display.h"
#include "driver/ambient.h"
#include "driver/imu.h"

// MUP6050
#define IMU_I2C_SDA 32
#define IMU_I2C_SCL 33

// 光感 (与MPU6050一致)
#define AMB_I2C_SDA 32
#define AMB_I2C_SCL 33

// TFT屏幕接口
#define LCD_BL_PIN 5
#define LCD_BL_PWM_CHANNEL 0

extern IMU mpu; 
extern SdCard tf;
extern Pixel rgb;
extern Display screen;     // 屏幕对象
extern Ambient ambLight;   // 光纤传感器对象
extern Config config;
extern TFT_eSPI tft;

void InitDevices();

#endif