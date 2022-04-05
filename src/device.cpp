#include "device.h"
#include <SPIFFS.h>
#include <esp32-hal.h>

IMU mpu; 
SdCard tf;
Pixel rgb;
Display screen;     // 屏幕对象
Ambient ambLight;   // 光纤传感器对象
Config config;
MPU_Config mpu_config;
TFT_eSPI tft(240, 280);
