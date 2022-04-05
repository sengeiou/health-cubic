#include "Common.h"
#include "pages/DailyDrink.h"
#include "pages/Weather.h"
#include "pages/DrinkChart.h"
#include "pages/DailyChart.h"
#include "pages/EditPage.h"
#include "notifies/DrinkNotify.h"

long timestamp = 0;

Page* pages[] = {
   new Weather(),
   new DailyDrink(),
   new DailyChart(),
   new DrinkChart()
};

Notify* notifies[] = {
	new DrinkNotify()
};

int PageCount()
{
	static int count = sizeof(pages) / sizeof(pages[0]);
	return count;
}

int NotifiesCount()
{
	static int count = sizeof(notifies) / sizeof(notifies[0]);
	return count;
}
