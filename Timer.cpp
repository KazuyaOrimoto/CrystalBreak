//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#include "Common.h"
#include "Timer.h"

Timer::Timer()
	:limitTime(60)
{
	startTime = GetNowCount();
	
}

Timer::~Timer()
{
}

void Timer::Update()
{
	int nowTime = GetNowCount();
	int elapsedTime = nowTime - startTime;
	remainderTime = limitTime - (elapsedTime / 1000);
}

bool Timer::CheckGameEndFlag()
{
	if (remainderTime <= 0)
	{
		return true;
	}
	return false;
}
