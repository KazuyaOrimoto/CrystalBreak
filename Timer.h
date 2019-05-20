//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#pragma once
class Timer
{
public:
	Timer();
	~Timer();
	void Update();
	int GetRemainderTime() { return remainderTime; }
	bool CheckGameEndFlag();
private:
	int startTime;
	const int limitTime;
	int  remainderTime;//残り時間
};

