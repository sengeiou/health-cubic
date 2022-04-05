#pragma once
#include <lvgl/lvgl.h>

extern "C" lv_font_t simhei_18;

class Style
{
public:
	static lv_style_t* Default()
	{
		static lv_style_t style;
		lv_style_init(&style);
		lv_style_set_bg_color(&style, LV_STATE_DEFAULT, LV_COLOR_BLACK);

		return &style;
	}

	static lv_style_t* WhiteFont()
	{
		static lv_style_t style;
		lv_style_init(&style);
		lv_style_set_text_opa(&style, LV_STATE_DEFAULT, LV_OPA_COVER);
		lv_style_set_text_color(&style, LV_STATE_DEFAULT, LV_COLOR_WHITE);

		return &style;
	}

	static lv_style_t* BlackFont()
	{
		static lv_style_t style;
		lv_style_init(&style);
		lv_style_set_text_opa(&style, LV_STATE_DEFAULT, LV_OPA_COVER);
		lv_style_set_text_color(&style, LV_STATE_DEFAULT, LV_COLOR_BLACK);

		return &style;
	}

	static lv_style_t* Simhei18()
	{
		static lv_style_t style;
		lv_style_init(&style);
		lv_style_set_text_opa(&style, LV_STATE_DEFAULT, LV_OPA_COVER);
		lv_style_set_text_font(&style, LV_STATE_DEFAULT, &simhei_18);
		return &style;
	}

	static lv_style_t* Monts24()
	{
		static lv_style_t style;
		lv_style_init(&style);
		lv_style_set_text_font(&style, LV_STATE_DEFAULT, &lv_font_montserrat_24);

		return &style;
	}

	static lv_style_t* Monts46()
	{
		static lv_style_t style;
		lv_style_init(&style);
		lv_style_set_text_font(&style, LV_STATE_DEFAULT, &lv_font_montserrat_48);

		return &style;
	}

private:

};
