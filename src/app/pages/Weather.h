#pragma once
#include "Page.h"

extern "C" lv_img_dsc_t binbao;
extern "C" lv_img_dsc_t lei;
extern "C" lv_img_dsc_t qing;
extern "C" lv_img_dsc_t shachen;
extern "C" lv_img_dsc_t wu;
extern "C" lv_img_dsc_t xue;
extern "C" lv_img_dsc_t yin;
extern "C" lv_img_dsc_t yu;
extern "C" lv_img_dsc_t yun;

struct WeatherData
{
	char city[20];
	char wea[20];
	char wea_img[20];
	const char* week;
	int hour;
	int minute;
	int month;
	int day;
};

class Weather : public Page
{
	bool showing = false;
	WeatherData data;
	lv_obj_t* l1, *l2, *l3;
	void UpdateText();

public:
	Weather() : data(WeatherData()) {}	

	virtual void Update(int tick) override;
	virtual void Show() override;
	virtual void Init() override;
	
	virtual void Close() override
	{
		showing = false;
		Page::Close();
	}
};