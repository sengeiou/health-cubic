#pragma once
#include "Page.h"
#include "../data/DrinkData.h"

class DrinkChart : public Page
{
public:
	virtual void Show() override
	{
        auto data = DrinkData::Instance();
        lv_obj_t* cont = Root();
        auto label = Label(cont, "近期饮水结构", Style::Simhei18());
        lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 15);
        int totle = Totle(data);
        if (totle <= 0) return;
        uint16_t start = 0;
        for (size_t i = 0; i < TYPE_SIZE; i++)
        {
            auto value = 360 * data.GetTypeValue(i) / totle;
            if (value == 0) value = 1;
            Arc(cont, start, start + value, i);
            start += value;
        }
	}

private:
    lv_color_t Color(int i)
    {
        switch (i)
        {
        case 0:
            return LV_COLOR_MAKE(205, 93, 92);
        case 1:
            return LV_COLOR_MAKE(186, 86, 212);
        case 2:
            return LV_COLOR_MAKE(250, 105, 179);
        case 3:
            return LV_COLOR_MAKE(250, 147, 20);
        case 4:
            return LV_COLOR_MAKE(227, 43, 117);
        case 5:
            return LV_COLOR_MAKE(66, 181, 212);
        case 6:
            return LV_COLOR_MAKE(135, 235, 51);
        default:
            return LV_COLOR_MAKE(240, 240, 240);
        }
    }

    int Totle(DrinkData& data)
    {
        int res = 0;
        for (size_t i = 0; i < TYPE_SIZE; i++)
        {
            res += data.GetTypeValue(i);
        }
        return res;
    }

    lv_obj_t* Arc(lv_obj_t* cont, uint16_t start, uint16_t end, int idx)
    {
        lv_obj_t* arc = lv_arc_create(cont, nullptr);
        lv_obj_add_style(arc, LV_BTN_PART_MAIN, Style::Default());
        lv_obj_set_style_local_border_width(arc, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
        lv_obj_set_style_local_pad_all(arc, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
        lv_obj_set_style_local_bg_opa(arc, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 1);
        lv_obj_set_style_local_line_color(arc, LV_ARC_PART_INDIC, LV_STATE_DEFAULT, Color(idx));
        lv_arc_set_bg_angles(arc, start, end);
        lv_arc_set_start_angle(arc, start);
        lv_arc_set_end_angle(arc, end);
        lv_obj_align(arc, NULL, LV_ALIGN_CENTER, 0, 10);
        return arc;
    }

};