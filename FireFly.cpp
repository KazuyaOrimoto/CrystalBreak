//-----------------------------------------------------------------------------//
//						必要なライブラリのインクルード
//-----------------------------------------------------------------------------//
#include "Common.h"
#include "EnemyBase.h"
#include "FireFly.h"
#include "ActionManager.h"
#include "Stage.h"
#include "Score.h"
#include "EffectCreater.h"
#include "SoundManager.h"

//-----------------------------------------------------------------------------//
//								コンストラクタ
//-----------------------------------------------------------------------------//
FireFly::FireFly(int sourceModelHandle, VECTOR startPos, ActionManager &actionManager)
	:EnemyBase(sourceModelHandle, startPos, actionManager,250)
{
	actionManager.SetCrystalIndexPair(indexPair);
	attackFlag = false;
}

//-----------------------------------------------------------------------------//
//								デストラクタ
//-----------------------------------------------------------------------------//
FireFly::~FireFly()
{
}

//-----------------------------------------------------------------------------//
//								アップデート処理
//-----------------------------------------------------------------------------//
void FireFly::Update(Stage &stage, ActionManager &actionManager)
{
	MV1SetPosition(modelHandle, position);
	if (isAlive == true)
	{
		time++;
		if (time % 20 == 0)
		{
			effectCreater->CreateCrystalEffect(position);
		}
	}
}

void FireFly::DieEffect()
{
	effectCreater->CreateTakeCrystalEffect(position);
	soundManager->PlayTakeCrystal();
}
