#include "Common.h"
#include "Dark.h"
#include "EffectCreater.h"
#include "SoundManager.h"
#include "Player.h"

Dark::Dark()
{
	effectCreater = EffectCreater::GetInstance();
	soundManager = SoundManager::GetInstance();
	start = false;
	warningGraph = LoadGraph("Texture/警告.png");
}

Dark::~Dark()
{
}

void Dark::Update(Player & player)
{
	warning = false;
	if (!start)
	{
		return;
	}
	if (player.GetPlayingExplosion())
	{
		return;
	}
	float nowPlayerHight = player.GetHight();
	//プレイヤーが同じ高さにいたとき
	if (beforePlayerHight == nowPlayerHight)
	{
		generationCount++;
	}
	//プレイヤーが同じ高さにいないとき
	else
	{
		generationCount = 0;
		beforePlayerHight = nowPlayerHight;
		swallowPlayer = false;
		playerDieCount = 0;
	}

	if (generationCount > 60 * 3)
	{
		darkPosition = player.GetExactlyPosition();
		effectCreater->CreateDrakEffect(darkPosition);
		soundManager->PlayTerror();
		generationCount = 0;
		swallowPlayer = true;
	}
	if (swallowPlayer)
	{
		playerDieCount++;
		warning = true;
		if (playerDieCount > 60 * 3)
		{
			player.SwallowDark(darkPosition);
			effectCreater->CreateSwallowEffect(darkPosition);
			generationCount = -9999999;
			playerDieCount = -9999999;
		}
	}
}

void Dark::Draw()
{
	if (warning)
	{
		DrawGraph(0,0, warningGraph,TRUE);
	}
}

void Dark::Start()
{
	start = true;
}
