#pragma once
#include "Page.h"
#include "../Style.h"
#include "../data/DrinkData.h"

class DailyChart : public Page
{
public:
	virtual void Show() override
	{
		auto data = DrinkData::Instance();
		auto max = GetMax();
		auto count = max / 300 + 1;
		lv_obj_t* cont = Container(Root());
		Label(cont, "近期饮水量", Style::Simhei18());
		lv_obj_t* chart = lv_chart_create(cont, NULL);
		lv_chart_set_range(chart, 0, 300 * count);
		lv_obj_set_size(chart, 200, 180);
		lv_chart_set_div_line_count(chart, count - 1, 0);
		lv_chart_set_point_count(chart, 7);
		lv_obj_add_style(chart, LV_CHART_PART_BG, Style::Default());
		lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
		lv_chart_series_t* s1 = lv_chart_add_series(chart, LV_COLOR_WHITE);
		lv_chart_set_next(chart, s1, data.GetDayValue(0));
		lv_chart_set_next(chart, s1, data.GetDayValue(1));
		lv_chart_set_next(chart, s1, data.GetDayValue(2));
		lv_chart_set_next(chart, s1, data.GetDayValue(3));
		lv_chart_set_next(chart, s1, data.GetDayValue(4));
		lv_chart_set_next(chart, s1, data.GetDayValue(5));
		lv_chart_set_next(chart, s1, data.GetDayValue(6));
	}

private:
	int GetMax()
	{
		int max = 0;
		for (size_t i = 0; i < DAY_SIZE; i++)
		{
			auto v = DrinkData::Instance().GetDayValue(i);
			if (v > max)
			{
				max = v;
			}
		}
		return max;
	}
};
