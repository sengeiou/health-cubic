#pragma once
#include "EditPage.h"
#include "app/app.h"
#include "../../driver/lv_port_indev.h"
#include "../data/DrinkData.h"

class DrinkInput : public EditPage
{
	lv_obj_t* drinkType = nullptr, * volume = nullptr;

	DrinkInput() {}

public:
	static DrinkInput* Instance()
	{
		static DrinkInput instance;
		return &instance;
	}

	virtual void HandleInput() override
	{
		auto type = lv_dropdown_get_selected(Instance()->drinkType);
		auto v = lv_dropdown_get_selected(Instance()->volume);
		DrinkData::Instance().AddDrink(type, v);
	}

	virtual void Show() override
	{
		lv_obj_t* cont = Container(Root());

		Label(cont, "补充水分", Style::Simhei18());
		drinkType = Dropdown(cont, "饮品", "水\n茶\n牛奶\n奶茶\n咖啡\n果汁\n其他", Style::Simhei18());
		volume = Dropdown(cont, "ml", "50\n100\n150\n200\n250\n300\n350\n400\n450\n500", Style::Simhei18());

		lv_obj_t* btn1 = lv_btn_create(cont, NULL);
		lv_obj_set_event_cb(btn1, event_handler);
		auto label = Label(btn1, "确 定", Style::Simhei18());
		lv_obj_add_style(label, LV_BTN_PART_MAIN, Style::BlackFont());

		lv_group_t * g = lv_group_create();
		lv_group_add_obj(g, drinkType);
		lv_group_add_obj(g, volume);
		lv_group_add_obj(g, btn1);
		lv_indev_set_group(indev_encoder, g);
	}

	static void event_handler(lv_obj_t* obj, lv_event_t event)
	{
		if (event == LV_EVENT_CLICKED) {
			Instance()->HandleInput();
			Instance()->Close();
			App::Instance().ExitEditPage();
		}
	}

};