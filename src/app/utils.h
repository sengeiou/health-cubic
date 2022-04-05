#pragma once
#include <lvgl/lvgl.h>
#include "Style.h"

lv_obj_t* Label(lv_obj_t* parent, const char* text, lv_style_t* font);

lv_obj_t* Container(lv_obj_t* parent);

lv_obj_t* Dropdown(lv_obj_t* parent, const char* value_str, const char* option);

lv_obj_t* PageRoot();