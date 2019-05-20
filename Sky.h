//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#pragma once

enum Day
{
	NOON,
	EVENING,
	NIGHT
};

class Sky
{
public:
	Sky();
	~Sky();
	void Update();
	void Draw();
private:
	int skyGraphHandle1;
	int skyGraphHandle2;
	int skyGraphHandle3;
	bool changeDay;
	int dayCount;
	int changeDayCount;
	Day nowDay;
	const int dayIndex = 3;
};

