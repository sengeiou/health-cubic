#include "DailyDrink.h"
#include "../data/DrinkData.h"
#include "../utils.h"
#include "../Style.h"

void ShowDrinkInfo(lv_obj_t* cont, const char* tip, int val)
{
    char str2[40];
    lv_snprintf(str2, sizeof(str2), "%s %d %s", tip, val, "ml");
    Label(cont, str2, Style::Simhei18());
}

void DailyDrink::Show()
{
    auto data = DrinkData::Instance();
    int end = data.TodayTotle() == 0 ? 360 : 360 * data.TodayCurrent() / data.TodayTotle();
    if (end > 360) end = 360;
    lv_obj_t* cont = Container(Root());
    lv_obj_t* arc = lv_arc_create(cont, nullptr);
    lv_obj_add_style(arc, LV_BTN_PART_MAIN, Style::Default());
    lv_obj_set_style_local_border_width(arc, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_pad_all(arc, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_arc_set_rotation(arc, 270);
    lv_arc_set_bg_angles(arc, 0, 360);
    lv_arc_set_start_angle(arc, 0);
    lv_arc_set_end_angle(arc, end);

    char str[10];
    auto percent = data.TodayTotle() == 0 ? 100 : 100 * data.TodayCurrent() / data.TodayTotle();
    lv_snprintf(str, sizeof(str), "%d %s", percent, "%");
    auto label = Label(arc, str, Style::Monts24());
    lv_obj_align(label, arc, LV_ALIGN_CENTER, 0, 0);

    ShowDrinkInfo(cont, "今日饮水", data.TodayCurrent());
    ShowDrinkInfo(cont, "计划饮水", data.TodayTotle());
}


