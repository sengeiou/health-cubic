#include "device.h"

void handle(ImuAction *act_info)
{
    Serial.printf("%d", act_info->active);
}

void setup()
{
    Serial.begin(115200);
    Serial.printf("正在初始化...");
    InitDevices();
    Serial.printf("初始化完成");
}

void loop()
{
    screen.routine();
    handle(mpu.update(200));
}

