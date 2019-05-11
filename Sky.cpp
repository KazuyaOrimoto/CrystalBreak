#include "Common.h"
#include "Sky.h"


Sky::Sky()
{
	skyGraphHandle1 = LoadGraph("Texture/Sky1.png");
	skyGraphHandle2 = LoadGraph("Texture/Sky2.png");
	skyGraphHandle3 = LoadGraph("Texture/Sky3.png");
	nowDay = NOON;
	dayCount = 0;
	changeDayCount = 0;
	changeDay = false;
}

Sky::~Sky()
{
}

void Sky::Update()
{
	if (changeDay)
	{
		changeDayCount++;
		if (changeDayCount > 255 * dayIndex)
		{
			changeDayCount = 0;
			dayCount = 0;
			changeDay = false;
			switch (nowDay)
			{
			case NOON:
				nowDay = EVENING;
				break;
			case EVENING:
				nowDay = NIGHT;
				break;
			case NIGHT:
				nowDay = NOON;
				break;
			default:
				break;
			}
		}
	}
	else if (dayCount > 60 * 1)
	{
		changeDay = true;
	}
	else
	{
		dayCount++;
	}
	
}

void Sky::Draw()
{
	switch (nowDay)
	{
	case NOON:
	{
		if (changeDay)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (int)changeDayCount / dayIndex);
			DrawGraph(0, 0, skyGraphHandle1, FALSE);

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)changeDayCount / dayIndex);
			DrawGraph(0, 0, skyGraphHandle2, FALSE);
		}
		else
		{
			DrawGraph(0, 0, skyGraphHandle1, FALSE);
		}
		break;
	}
	case EVENING:
	{
		if (changeDay)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (int)changeDayCount / dayIndex);
			DrawGraph(0, 0, skyGraphHandle2, FALSE);

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)changeDayCount / dayIndex);
			DrawGraph(0, 0, skyGraphHandle3, FALSE);
		}
		else
		{
			DrawGraph(0, 0, skyGraphHandle2, FALSE);
		}
		break;
	}
	case NIGHT:
	{
		if (changeDay)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (int)changeDayCount / dayIndex);
			DrawGraph(0, 0, skyGraphHandle3, FALSE);

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)changeDayCount / dayIndex);
			DrawGraph(0, 0, skyGraphHandle1, FALSE);
		}
		else
		{
			DrawGraph(0, 0, skyGraphHandle3, FALSE);
		}
		break;
	}
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
