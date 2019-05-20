//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#include "Common.h"
#include "PlaySceneUI.h"
#include "Player.h"
#include "Score.h"
#include "Timer.h"

PlaySceneUI::PlaySceneUI()
{
	uiGraphHandle = LoadGraph("Texture/UI.png");
	LoadDivGraph("Texture/Number40.png", 10, 10, 1, 99, 130, numberGraph40);
	LoadDivGraph("Texture/Number18.png", 10, 10, 1, 50, 62, numberGraph18);
	timeraph = LoadGraph("Texture/Layer 0.png");
	scoreInstance = Score::GetInstance();

	AddFontResourceEx("Font/Molot.otf", FR_PRIVATE, NULL);
	ChangeFont("Molot", DX_CHARSET_DEFAULT);
}

PlaySceneUI::~PlaySceneUI()
{
}

void PlaySceneUI::Update(Player& player, Timer& timer)
{
	playerBombNum = player.GetPlayerBombNum();
	time = timer.GetRemainderTime();
	scorepoint = scoreInstance->GetScore();
	height = scoreInstance->GetHeight() * 5;
}

void PlaySceneUI::Draw()
{
	DrawGraph(0, 0, uiGraphHandle, TRUE);
	SetFontSize(110);
	DrawNumber(numberGraph40, 1702, 945, playerBombNum, 2, 81, GetColor(255, 255, 255));
	DrawTime();
	SetFontSize(150);
	if (time > 20)
	{
		DrawNumber(numberGraph40, 1592, 660, time, 2, 90, GetColor(255, 255, 255));
	}
	else
	{
		DrawNumber(numberGraph40, 1592, 660, time, 2, 90, GetColor(255, 0, 0));
	}
	SetFontSize(80);
	DrawNumber(numberGraph18, 1536, 372, scorepoint, 6, 63, GetColor(255, 255, 255));
	SetFontSize(110);
	DrawNumber(numberGraph18, 1531, 107, height, 5, 78, GetColor(255, 255, 255));
}

void PlaySceneUI::DrawNumber(int graphHandle[], int x, int y, int number, int length, int sizeX, int color)
{
	int drawCount = 0;
	drawCount = (int)log10(number) + 1;
	int zeroDrawCount = length - (drawCount);
	for (int i = length; i > 0; i--)
	{
		if (zeroDrawCount)
		{
			zeroDrawCount--;
			//DrawGraph(x + (sizeX * (length - i)), y, graphHandle[0], TRUE);
			DrawFormatString(x + (sizeX * (length - i)), y, color, "0");
		}
		else
		{
			int num = number;
			for (int j = 0; j < i; j++)
			{
				if (j != i - 1)
				{
					num /= 10;
				}
				else
				{
					num %= 10;
				}
			}
			//DrawGraph(x + (sizeX * (length - i)), y, graphHandle[num], TRUE);
			DrawFormatString(x + (sizeX * (length - i)), y, color, "%d", num);
			drawCount--;
		}
	}
}

void PlaySceneUI::DrawTime()
{
	int y = int(212.0 / 60.0) * time;
	DrawRectGraph(1575, 630 + (212 - y), 0, (212 - y), 212, y, timeraph, TRUE, FALSE);
}
