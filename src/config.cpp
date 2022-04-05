#include <Preferences.h>
#include "device.h"
#include "config.h"

Preferences prefs;        // 声明Preferences对象

void config_read(const char *file_path, Config *cfg)
{
    prefs.begin("sys"); // 打开命名空间mynamespace
    cfg->backLight = prefs.getUChar("backLight", 80);
    cfg->rotation = prefs.getUChar("rotation", 4);
    cfg->auto_calibration_mpu = prefs.getUChar("auto_mpu", 1);
    cfg->mpu_order = prefs.getUChar("mpu_order", 0);
    prefs.end(); // 关闭当前命名空间
}

void config_save(const char *file_path, Config *cfg)
{
    prefs.begin("sys"); // 打开命名空间mynamespace
    prefs.putUChar("backLight", cfg->backLight);
    prefs.putUChar("rotation", cfg->rotation);
    prefs.putUChar("auto_mpu", cfg->auto_calibration_mpu);
    prefs.putUChar("mpu_order", cfg->mpu_order);
    prefs.end(); // 关闭当前命名空间
}

void mpu_config_read(const char *file_path, MPU_Config *cfg)
{
    prefs.begin("MPU_Config"); // 打开命名空间mynamespace
    cfg->x_gyro_offset = prefs.getInt("x_gyro_offset", 0);
    cfg->y_gyro_offset = prefs.getInt("y_gyro_offset", 0);
    cfg->z_gyro_offset = prefs.getInt("z_gyro_offset", 0);
    cfg->x_accel_offset = prefs.getInt("x_accel_offset", 0);
    cfg->y_accel_offset = prefs.getInt("y_accel_offset", 0);
    cfg->z_accel_offset = prefs.getInt("z_accel_offset", 0);
    prefs.end(); // 关闭当前命名空间
}

void mpu_config_save(const char *file_path, MPU_Config *cfg)
{
    prefs.begin("MPU_Config"); // 打开命名空间mynamespace
    prefs.putInt("x_gyro_offset", cfg->x_gyro_offset);
    prefs.putInt("y_gyro_offset", cfg->y_gyro_offset);
    prefs.putInt("z_gyro_offset", cfg->z_gyro_offset);
    prefs.putInt("x_accel_offset", cfg->x_accel_offset);
    prefs.putInt("y_accel_offset", cfg->y_accel_offset);
    prefs.putInt("z_accel_offset", cfg->z_accel_offset);

    prefs.end(); // 关闭当前命名空间
}