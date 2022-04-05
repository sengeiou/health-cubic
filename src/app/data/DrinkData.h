#pragma once
#define TYPE_SIZE 7
#define DAY_SIZE 7

class DrinkData
{
	int todayTotle = 1000;
	int today = 0;

	int types[TYPE_SIZE] = { 100, 200, 60, 50, 40, 30 };
	int day[DAY_SIZE] = { 900, 920, 915, 100, 950, 1100, 950 };

	DrinkData() {}

public:
	static DrinkData& Instance()
	{
		static DrinkData data;
		return data;
	}

	void ReadData()
	{

	}

	void SaveData()
	{

	}

	int TodayTotle()
	{
		return todayTotle;
	}

	int TodayCurrent()
	{
		return day[DAY_SIZE - 1];
	}

	void AddDrink(int idx, int value)
	{
		day[DAY_SIZE - 1] += value;
		if (idx >= 0 && idx < TYPE_SIZE)
		{
			types[idx] += value;
		}
	}

	int GetTypeValue(int idx)
	{
		if (idx >= 0 && idx < TYPE_SIZE)
		{
			return types[idx];
		}
		return -1;
	}

	int GetDayValue(int idx)
	{
		if (idx >= 0 && idx < DAY_SIZE)
		{
			return day[idx];
		}
		return -1;
	}

private:

};