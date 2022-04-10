#pragma once
#include "Notify.h"
#include "../pages/DrinkInput.h"
#include "../app.h"

#define OFFSET 3600000

class DrinkNotify : public Notify
{
	long time = App::Instance().timestamp + OFFSET;

public:
	DrinkNotify()
	{
		// page = DrinkInput::Instance();
	}

	virtual bool IsNotify(long current)
	{
		if (current > time)
		{
			time = current + OFFSET;
			return true;
		}
		return false;
	}
};
