#pragma once
#include "../device.h"
#include "../driver/lv_port_fatfs.h"
#include <lvgl/lvgl.h>
#include <WiFi.h>  
#include "Common.h"
#include "pages/InitPage.h"

#define AUTO_TURN_TIME 30000
#define SSID "Xiaomi_0D32"
#define PASSWORD "88888888"

class App
{
	int current = 0;
	int autoTurnTime = 0;
	lv_task_t* task = nullptr;
	EditPage* editPage = nullptr;

	static void TaskHandle(lv_task_t* task)
	{
		App::Instance().Update(task->period);
	}

	void ChangePage(int next)
	{
		if (next < 0 || next >= PageCount()) return;
		pages[current]->Close();
		pages[next]->Show();
		current = next;
		autoTurnTime = 0;
	}

	void Update(uint32_t period)
	{
		UpdateData(period);
		//if (HasNotifies()) return;
		AutoNextPage(period);
	}

	void UpdateData(uint32_t period)
	{
		for (size_t i = 0; i < PageCount(); i++)
		{
			pages[i]->Update(period);
		}
	}

	bool HasNotifies()
	{
		if (editPage != nullptr) return true;
		for (size_t i = 0; i < NotifiesCount(); i++)
		{
			if (notifies[i]->Handle(timestamp, &editPage) && editPage != nullptr)
			{
				pages[current]->Close();
				editPage->Show();
				return true;
			}
		}
		return false;
	}

	void AutoNextPage(uint32_t period)
	{
		autoTurnTime += period;
		if (autoTurnTime >= AUTO_TURN_TIME)
		{
			TurnRight();
		}
	}

	void InitWifi()
	{
		WiFi.enableSTA(true);
    	WiFi.begin(SSID, PASSWORD);
		int i = 0;
		while (WL_CONNECTED != WiFi.status() && i < 3)
		{
			delay(1000);
			i++;
		}
	 	if (WL_CONNECTED != WiFi.status())
        {
            Serial.println(F("\nWiFi connect error.\n"));
        }
	}

	App() { }

public:
	long long timestamp = 0;

	static App& Instance() {
		static App instance;
		return instance;
	}

	void Init()
	{
		Serial.println("正在初始化...");
		if (!SPIFFS.begin(true))
		{
			Serial.println("SPIFFS Mount Failed");
			return;
		}
		config_read(nullptr, &config);
		mpu_config_read(nullptr, &mpu_config);
		screen.init(config.rotation, config.backLight);

		InitPage init;
		init.Show();

		InitWifi();
		
		rgb.init();
		rgb.setBrightness(0.05).setRGB(0, 64, 64);
		ambLight.init(ONE_TIME_H_RESOLUTION_MODE);
		tf.init();
		lv_fs_if_init();
		lv_port_indev_init();
		mpu.init(config.mpu_order, config.auto_calibration_mpu, &mpu_config); // 初始化比较耗时
		RgbParam rgb_setting = {LED_MODE_HSV, 1, 32, 255, 255, 255, 255, 1, 1, 1, 0.15, 0.25, 0.001, 30};
		rgb_thread_init(&rgb_setting);

		for (size_t i = 0; i < PageCount(); i++)
		{
			pages[i]->Init();
		}
		Serial.println("初始化完成!");

		pages[current]->Show();
		task = lv_task_create(TaskHandle, 1000, LV_TASK_PRIO_MID, this);
	}

	void ExitEditPage()
	{
		if (editPage != nullptr)
		{
			editPage->Close();
			editPage = nullptr;
		}
		pages[current]->Show();
	}

	void TurnLeft()
	{
		ChangePage(current == 0 ? PageCount() - 1 : current - 1);
	}

	void TurnRight()
	{
		ChangePage(current == PageCount() - 1 ? 0 : current + 1);
	}

	void ButtonDown()
	{

	}

};