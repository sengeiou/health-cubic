#include "device.h"
#include "app/app.h"

ImuAction *act_info;    

void handle(ImuAction *act_info)
{
    if (TURN_LEFT == act_info->active)
    {
        App::Instance().TurnLeft();
        delay(300);
    }
    else if (TURN_RIGHT == act_info->active)
    {
        App::Instance().TurnRight();
        delay(300);
    }
    else if (GO_FORWORD == act_info->active)
    {
        
    }
    act_info->active = UNKNOWN;
    act_info->isValid = 0;
}

void setup()
{
    Serial.begin(115200);
    App::Instance().Init();
}

void loop()
{
    screen.routine();
    act_info = mpu.update(200);
    handle(act_info);
}

