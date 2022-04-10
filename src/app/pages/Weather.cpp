#include "Weather.h"
#include <HTTPClient.h>
#include <ESP32Time.h>
#include <ArduinoJson.h>
#include "../utils.h"
#include "../app.h"

#define WEATHER_IMAGE(wea_img, test) \
	if (strcmp(wea_img, #test) == 0) \
	return &test
#define WEATHER_API_URL "https://www.yiketianqi.com/free/day?appid=17556252&appsecret=ZPppO4HF&unescape=1"
#define TIME_API_URL "http://api.m.taobao.com/rest/api3.do?api=mtop.common.gettimestamp"
#define TIMEZERO_OFFSIZE (28800000) // 8小时

int updateTime = 0;
constexpr auto GET_DATA_TIME = 30 * 60 * 1000;
static const char weeks[7][4] = { "日", "一", "二", "三", "四", "五", "六"};

const char *Week(int day)
{
	if (day < 0 || day > 6)
		return "";
	return weeks[day];
}

void UpdateTime(WeatherData *data)
{
	ESP32Time espTime;
	espTime.setTime(App::Instance().timestamp / 1000);
	data->week = Week(espTime.getDayofWeek());
	data->day = espTime.getDay();
	data->month = espTime.getMonth() + 1;
	data->hour = espTime.getHour(true);
	data->minute = espTime.getMinute();
}

void GetWeather(WeatherData *data)
{
	HTTPClient http;
	http.setTimeout(1000);
	http.begin(WEATHER_API_URL);
	if (http.GET() == HTTP_CODE_OK)
	{
		String payload = http.getString();
		DynamicJsonDocument doc(1024);
		deserializeJson(doc, payload);
		JsonObject sk = doc.as<JsonObject>();
		strcpy(data->city, sk["city"].as<String>().c_str());
		strcpy(data->wea, sk["wea"].as<String>().c_str());
		strcpy(data->wea_img, sk["wea_img"].as<String>().c_str());
	}
	else
	{
		Serial.println("获取天气数据错误");
	}
}

void GetTime(WeatherData *data)
{
	HTTPClient http;
	http.setTimeout(1000);
	http.begin(TIME_API_URL);
	if (http.GET() == HTTP_CODE_OK)
	{
		String payload = http.getString();
		DynamicJsonDocument doc(1024);
		deserializeJson(doc, payload);
		JsonObject sk = doc.as<JsonObject>();
		App::Instance().timestamp = atoll(sk["data"]["t"].as<String>().c_str()) + TIMEZERO_OFFSIZE;
		UpdateTime(data);
	}
	else
	{
		Serial.println("获取时间错误");
	}
}

void GetData(WeatherData *data)
{
	GetWeather(data);
	GetTime(data);
}

lv_img_dsc_t *GetWeatherImage(const char *wea_img)
{
	WEATHER_IMAGE(wea_img, binbao);
	WEATHER_IMAGE(wea_img, lei);
	WEATHER_IMAGE(wea_img, qing);
	WEATHER_IMAGE(wea_img, shachen);
	WEATHER_IMAGE(wea_img, wu);
	WEATHER_IMAGE(wea_img, xue);
	WEATHER_IMAGE(wea_img, yin);
	WEATHER_IMAGE(wea_img, yu);
	return &yun;
}

void Weather::Update(int tick)
{
	updateTime += tick;
	App::Instance().timestamp += tick;
	UpdateTime(&data);
	UpdateText();
	if (updateTime < GET_DATA_TIME)
	{
		return;
	}
	updateTime = 0;
	GetData(&data);
}

lv_obj_t *Label(lv_obj_t *parent, lv_style_t *font)
{
	auto label = lv_label_create(parent, nullptr);
	lv_obj_add_style(label, LV_BTN_PART_MAIN, Style::WhiteFont());
	lv_obj_add_style(label, LV_LABEL_PART_MAIN, font);
	return label;
}

void Weather::Show()
{
	showing = true;
	lv_obj_t *cont = Container(Root());
	auto image = lv_img_create(cont, NULL);
	lv_img_set_src(image, GetWeatherImage(data.wea_img));

	l1 = Label(cont, Style::Simhei18());
	l2 = Label(cont, Style::Monts46());
	l3 = Label(cont, Style::Simhei18());
	UpdateText();
}

void Weather::UpdateText()
{
	if (showing)
	{
		lv_label_set_text_fmt(l1, "%s %s\0", data.city, data.wea);
		lv_label_set_text_fmt(l2, "%02d : %02d\0", data.hour, data.minute);
		lv_label_set_text_fmt(l3, "%2d月%2d日 周%s", data.month, data.day, data.week);
	}
}

void Weather::Init()
{
	GetData(&data);
}
