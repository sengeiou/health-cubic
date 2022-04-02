#include "device.h"
#include <SPIFFS.h>
#include <esp32-hal.h>
#include "driver/lv_port_indev.h"
#include "driver/lv_port_fatfs.h"

IMU mpu; 
SdCard tf;
Pixel rgb;
Display screen;     // 屏幕对象
Ambient ambLight;   // 光纤传感器对象
Config config;
TFT_eSPI tft(240, 280);

void InitDevices()
{
    // 需要放在Setup里初始化
    if (!SPIFFS.begin(true))
    {
        Serial.println("SPIFFS Mount Failed");
        return;
    }

    config_read(nullptr, &config);

    /*** Init screen ***/
    screen.init(config.rotation, config.backLight);

    /*** Init on-board RGB ***/
    rgb.init();
    rgb.setBrightness(0.05).setRGB(0, 64, 64);

    /*** Init ambient-light sensor ***/
    ambLight.init(ONE_TIME_H_RESOLUTION_MODE);

    /*** Init micro SD-Card ***/
    tf.init();
    lv_fs_if_init();

    /*** Init IMU as input device ***/
    lv_port_indev_init();
    mpu.init(config.mpu_order, config.auto_calibration_mpu, &config.mpu_config); // 初始化比较耗时

    // 初始化RGB灯 HSV色彩模式
    RgbParam rgb_setting = {LED_MODE_HSV, 1, 32, 255, 255, 255, 255, 1, 1, 1, 0.15, 0.25, 0.001, 30};
    // 初始化RGB任务
    rgb_thread_init(&rgb_setting);
}