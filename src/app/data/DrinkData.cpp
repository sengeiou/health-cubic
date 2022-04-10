#include "DrinkData.h"

DrinkData& DrinkData::Instance()
{
    static DrinkData data;
    return data;
}