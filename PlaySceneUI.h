//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#pragma once

class Player;
class Timer;
class Score;

class PlaySceneUI
{
public:
	PlaySceneUI();
	~PlaySceneUI();
	void Update(Player& player,Timer& timer);
	void Draw();
	int GetScore() { return scorepoint; }
	int GetHeight() { return height; }
private:

	void DrawNumber(int graphHandle[],int x,int y,int number,int length,int sizeX,int color);
	void DrawTime();

	int uiGraphHandle;
	int numberGraph40[10];
	int numberGraph18[10];
	int playerBombNum;
	int time;
	int scorepoint;
	int height;

	int timeraph;
	Score* scoreInstance;
};

