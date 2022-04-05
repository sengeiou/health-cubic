#pragma once
#include "Notify.h"
#include "../pages/DrinkInput.h"

class DrinkNotify : public Notify
{
public:
	DrinkNotify()
	{
		page = DrinkInput::Instance();
	}

	virtual bool IsNotify(long current)
	{
		return true;
	}
};
