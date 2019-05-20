//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#include "Common.h"
#include "ActionManager.h"
#include "EnemyBase.h"
//-----------------------------------------------------------------------------//
//								コンストラクタ
//-----------------------------------------------------------------------------//
ActionManager::ActionManager()
{
	playerIndexPair = {0,0};
	deleteEnemy = NULL;
}

//-----------------------------------------------------------------------------//
//								デストラクタ
//-----------------------------------------------------------------------------//
ActionManager::~ActionManager()
{
	enemyIndexPairMap.clear();
	nextIndexPairMap.clear();
	crystalIndexPair.clear();
	deleteEnemy = NULL;
}

//-----------------------------------------------------------------------------//
//						プレイヤーの要素位置をセット
//-----------------------------------------------------------------------------//
void ActionManager::SetPlayerIndexPair(IndexPair pair)
{
	playerIndexPair = pair;
}

//-----------------------------------------------------------------------------//
//					エネミーのポインタを要素位置をMapに挿入
//-----------------------------------------------------------------------------//
void ActionManager::InsertEnemyIndexPair(EnemyBase* enemy, IndexPair pair)
{
	//渡されてきたエネミーのポインタと位置を追加
	enemyIndexPairMap.insert(std::make_pair(enemy, pair));
}

//-----------------------------------------------------------------------------//
//					位置が変わったエネミーの要素位置をセット
//-----------------------------------------------------------------------------//
void ActionManager::SetEnemyIndexPair(EnemyBase * enemy, IndexPair pair)
{
	//登録されているエネミーのポインタの位置を書き換える
	enemyIndexPairMap.at(enemy) = pair;
	nextIndexPairMap.erase(enemy);
}

//-----------------------------------------------------------------------------//
//						プレイヤーのアクションを返す
//-----------------------------------------------------------------------------//
Action ActionManager::ReturnPlayerAction(Direction playerDirection)
{
	switch (playerDirection)
	{
	case UP:
	{
		//プレイヤーの要素位置の一つ上を攻撃するか
		IndexPair serchIndex = playerIndexPair.IndexPairUp();
		if (IsPlayerAttack(serchIndex))
		{
			return ATTACK;
		}
		else
		{
			return NO_ACTION;
		}
		break;
	}
	case DOWN:
	{
		//プレイヤーの要素位置の一つ下を攻撃するか
		IndexPair serchIndex = playerIndexPair.IndexPairDown();;
		if (IsPlayerAttack(serchIndex))
		{
			return ATTACK;
		}
		else
		{
			return NO_ACTION;
		}
		break;
	}
	case RIGHT:
	{
		//プレイヤーの要素位置の一つ右を攻撃するか
		IndexPair serchIndex = playerIndexPair.IndexPairRight();
		if (IsPlayerAttack(serchIndex))
		{
			return ATTACK;
		}
		else
		{
			return MOVE;
		}
		break;
	}
	case LEFT:
	{
		//プレイヤーの要素位置の一つ左を攻撃するか
		IndexPair serchIndex = playerIndexPair.IndexPairLeft();
		if (IsPlayerAttack(serchIndex))
		{
			return ATTACK;
		}
		else
		{
			return MOVE;
		}
		break;
	}
	case NO_DIRECTION:
	{
		//プレイヤーの要素位置の一つ下を攻撃するか
		IndexPair serchIndex = playerIndexPair.IndexPairDown();
		if (IsPlayerAttack(serchIndex))
		{
			return ATTACK;
		}
		else
		{
			return NO_ACTION;
		}
		break;
	}
	default:
	{
		break;
	}
	}
	return NO_ACTION;
}

//-----------------------------------------------------------------------------//
//						エネミーのアクションを返す
//-----------------------------------------------------------------------------//
Action ActionManager::ReturnEnemyAction(EnemyBase* enemy, Direction enemyDirection)
{
	if (enemyDirection == RIGHT)
	{
		IndexPair serchIndex = enemyIndexPairMap.at(enemy).IndexPairRight();
		if (IsEnemyAttack(serchIndex))
		{
			return ATTACK;
		}
		else
		{
			return NO_ACTION;
		}
	}
	else if (enemyDirection == LEFT)
	{
		IndexPair serchIndex = enemyIndexPairMap.at(enemy).IndexPairLeft();
		if (IsEnemyAttack(serchIndex))
		{
			return ATTACK;
		}
		else
		{
			return NO_ACTION;
		}
	}
	return NO_ACTION;
}

void ActionManager::DeleteEnemy(EnemyBase * enemy)
{
	enemyIndexPairMap.erase(enemy);
	nextIndexPairMap.erase(enemy);
}

void ActionManager::AttackEnemy(IndexPair serchIndex , Player & player)
{
	for (auto itr : enemyIndexPairMap)
	{
		if (itr.second.x == serchIndex.x && itr.second.y == serchIndex.y)
		{
			deleteEnemy = itr.first;
			break;
		}
	}
	for (auto itr : nextIndexPairMap)
	{
		if (itr.second.x == serchIndex.x && itr.second.y == serchIndex.y)
		{
			deleteEnemy = itr.first;
			break;
		}
	}

	auto itr = crystalIndexPair.begin();

	while (itr != crystalIndexPair.end())
	{
		if ((*itr).x == serchIndex.x && (*itr).y == serchIndex.y)
		{
			itr = crystalIndexPair.erase(itr);
		}
		else
		{
			itr++;
		}
	}

	if (deleteEnemy == NULL)
	{
		return;
	}
	deleteEnemy->Attacked(player);
	DeleteEnemy(deleteEnemy);
	deleteEnemy = NULL;
}

void ActionManager::SetCrystalIndexPair(IndexPair indexPair)
{
	crystalIndexPair.push_back(indexPair);
}

bool ActionManager::CanMovePlayer(IndexPair indexPair)
{
	for (auto itr : enemyIndexPairMap)
	{
		if (itr.second.x == indexPair.x && itr.second.y == indexPair.y)
		{
			return false;
		}
		
	}
	for (auto itr : nextIndexPairMap)
	{
		if (itr.second.x == indexPair.x && itr.second.y == indexPair.y)
		{
			return false;
		}

	}
	for (auto itr : crystalIndexPair)
	{
		if (itr.x == indexPair.x && itr.y == indexPair.y)
		{
			return false;
		}
	}
	return true;
}

void ActionManager::SetMoveEnemyIndexPair(EnemyBase* enemy, IndexPair nextindexPair)
{
	nextIndexPairMap.insert(std::make_pair(enemy, nextindexPair));
}

void ActionManager::EnemyDataClear()
{
	enemyIndexPairMap.clear();
	nextIndexPairMap.clear();
	crystalIndexPair.clear();

}

//-----------------------------------------------------------------------------//
//								プレイヤーが攻撃するか
//-----------------------------------------------------------------------------//
bool ActionManager::IsPlayerAttack(IndexPair serchIndex)
{
	for (auto itr : enemyIndexPairMap)
	{
		if (itr.second.x == serchIndex.x && itr.second.y == serchIndex.y)
		{
			deleteEnemy = itr.first;
			return true;
		}
	}
	return false;
}

bool ActionManager::IsEnemyAttack(IndexPair serchIndex)
{
	if (serchIndex.x == playerIndexPair.x && serchIndex.y == playerIndexPair.y)
	{
		return true;
	}
	return false;
}
