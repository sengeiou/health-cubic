#pragma once
#include "../pages/EditPage.h"

class Notify
{
protected:
	EditPage* page = nullptr;

public:
	virtual bool Handle(long current, EditPage** page)
	{
		if (!IsNotify(current)) return false;
		*page = this->page;
		return true;
	}

	virtual bool IsNotify(long current) = 0;
};