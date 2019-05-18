//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//
#include "Common.h"
#include "EnemyList.h"
#include "EnemyBase.h"
#include "FireFly.h"
#include "Boar.h"
#include "Stage.h"

//-----------------------------------------------------------------------------//
//								コンストラクタ
//-----------------------------------------------------------------------------//
EnemyList::EnemyList(ActionManager &actionManager, Stage & stage)
{
	fireFlyModelHandle = MV1LoadModel("model/Crystal.mqo");
	boarModelHandle = MV1LoadModel("model/EnemyRock.mqo");
	stage.GetMapData(map);
	CreateEnemy(actionManager);
}

//-----------------------------------------------------------------------------//
//								デストラクタ
//-----------------------------------------------------------------------------//
EnemyList::~EnemyList()
{
	for (auto itr : enemyList)
	{
		delete(itr);
	}
	enemyList.clear();
}

//-----------------------------------------------------------------------------//
//								アップデート処理
//-----------------------------------------------------------------------------//
void EnemyList::Update(Stage &stage, ActionManager &actionManager)
{
	std::vector<EnemyBase*>::iterator itr = enemyList.begin();
	while (itr != enemyList.end())
	{
		if ((*itr)->isActive() == false)
		{
			itr = enemyList.erase(itr);
		}
		else
		{
			itr++;
		}
	}
	for (auto itr : enemyList)
	{
		if (needDrawModel(itr->GetPosition()))
		{
			itr->Update(stage, actionManager);
		}
	}
}

//-----------------------------------------------------------------------------//
//								描画処理
//-----------------------------------------------------------------------------//
void EnemyList::Draw()
{
	for (auto itr : enemyList)
	{
		if (needDrawModel(itr->GetPosition()))
		{
			itr->Draw();
		}
	}
}

//-----------------------------------------------------------------------------//
//							エネミーリストを渡す
//-----------------------------------------------------------------------------//
EnemyVector EnemyList::GetEnemyList()
{
	return enemyList;
}

void EnemyList::NextStageCreate(Stage & stage, ActionManager & actionManager)
{
	for (auto itr : enemyList)
	{
		itr->NextStageCreate();
	}
	stage.GetMapData(map);
	enemyList.clear();
	CreateEnemy(actionManager);
}

//-----------------------------------------------------------------------------//
//								エネミーを作成
//-----------------------------------------------------------------------------//
void EnemyList::CreateEnemy(ActionManager &actionManager)
{
	for (int i = 0; i < BLOCK_NUM_X; i++)
	{
		for (int j = 0; j < BLOCK_NUM_Y; j++)
		{
			switch (map[j][i])
			{
			case NO_ENEMY:
			{
				break;
			}
			case FIRE_FLY:
			{
				enemyList.push_back(new FireFly(fireFlyModelHandle, VGet(float(i * BLOCK_SIZE), float(-j * BLOCK_SIZE), 0.0f), actionManager));
				break;
			}
			case BOAR:
			{
				enemyList.push_back(new Boar(boarModelHandle, VGet(float(i * BLOCK_SIZE), float(-j * BLOCK_SIZE), 0.0f), actionManager));
				break;
			}
			default:
			{
				break;
			}
			}
		}
	}
}

bool EnemyList::needDrawModel(VECTOR position)
{
	VECTOR boxPos1 = VGet(position.x + MAGNIFICATION_RATE, position.y + MAGNIFICATION_RATE, position.z + MAGNIFICATION_RATE);
	VECTOR boxPos2 = VGet(position.x - MAGNIFICATION_RATE, position.y - MAGNIFICATION_RATE, position.z - MAGNIFICATION_RATE);
	bool needDraw = CheckCameraViewClip_Box(boxPos1, boxPos2);
	return !needDraw;
}
