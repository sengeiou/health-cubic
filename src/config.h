#ifndef CONFIG_H
#define CONFIG_H
#include <WString.h>

struct MPU_Config
{
    int16_t x_gyro_offset;
    int16_t y_gyro_offset;
    int16_t z_gyro_offset;

    int16_t x_accel_offset;
    int16_t y_accel_offset;
    int16_t z_accel_offset;
};

struct Config
{
    uint8_t backLight;            // 屏幕亮度（1-100）
    uint8_t rotation;             // 屏幕旋转方向
    uint8_t auto_calibration_mpu; // 是否自动校准陀螺仪 0关闭自动校准 1打开自动校准
    uint8_t mpu_order;
};

void config_read(const char *file_path, Config *cfg);

void config_save(const char *file_path, Config *cfg);

void mpu_config_read(const char *file_path, MPU_Config *cfg);

void mpu_config_save(const char *file_path, MPU_Config *cfg);

#endif