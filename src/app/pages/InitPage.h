#pragma once
#include "Page.h"

class InitPage : public Page
{
public:
	virtual void Show() override
	{
		lv_obj_t* cont = Container(Root());
		Label(cont, "正在加载...", Style::Simhei18());
		delay(300);
	}
};
