#include "utils.h"

lv_obj_t* Label(lv_obj_t* parent, const char* text, lv_style_t* font)
{
    auto label = lv_label_create(parent, nullptr);
    lv_obj_add_style(label, LV_BTN_PART_MAIN, Style::WhiteFont());
    lv_obj_add_style(label, LV_LABEL_PART_MAIN, font);
    lv_label_set_text(label, text);
    return label;
}

lv_obj_t* Container(lv_obj_t* parent)
{
    auto cont = lv_cont_create(parent, NULL);
    lv_obj_add_style(cont, LV_BTN_PART_MAIN, Style::Default());
    lv_obj_set_style_local_border_width(cont, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_auto_realign(cont, true);                    /*Auto realign when the size changes*/
    lv_obj_align_origo(cont, NULL, LV_ALIGN_CENTER, 0, 0);  /*This parametrs will be sued when realigned*/
    lv_cont_set_fit(cont, LV_FIT_TIGHT);
    lv_cont_set_layout(cont, LV_LAYOUT_COLUMN_MID);
    return cont;
}

lv_obj_t* Dropdown(lv_obj_t* parent, const char* value_str, const char* option)
{
    lv_obj_t* obj = lv_dropdown_create(parent, NULL);
    lv_obj_add_style(obj, LV_CONT_PART_MAIN, Style::Default());
    lv_obj_add_style(obj, LV_CONT_PART_MAIN, Style::WhiteFont());
    lv_obj_set_style_local_value_str(obj, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, value_str);
    lv_obj_set_style_local_value_color(obj, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_set_width(obj, 200);
    lv_dropdown_set_options(obj, option);

    return obj;
}

lv_obj_t* PageRoot()
{
    auto root = lv_obj_create(lv_scr_act(), nullptr);
    lv_obj_add_style(root, LV_BTN_PART_MAIN, Style::Default());
    lv_obj_set_size(root, LV_HOR_RES, LV_VER_RES);
    lv_obj_set_style_local_radius(root, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_border_width(root, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    return root;
}
