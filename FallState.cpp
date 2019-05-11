#include "Common.h"
#include "PlayerState.h"
#include "FallState.h"
#include "InputMAnager.h"
#include "Stage.h"
#include "Player.h"
#include "NoActionState.h"
#include "ActionManager.h"

FallState::FallState()
	: PlayerState()
{
}

FallState::~FallState()
{
}

PlayerState* FallState::Update(Player& player, Stage& stage, InputManager& inputManager, ActionManager& actionManager)
{
	VECTOR playerPosition = player.GetPosition();
	VECTOR playerExactlyPosition = player.GetExactlyPosition();
	float falledPositionY = (float)(int)(playerExactlyPosition.y - BLOCK_SIZE);		//落ち終わった後のポジション
	float nextPosition = playerPosition.y - fallSpeed;						//このフレームでそのまま落下したときのポジション
	IndexPair nextIndexPair = player.GetIndexPair().IndexPairDown();
	bool onGround;
	if (player.GetPosition().y < 0)
	{
		onGround = stage.CheckOnGround(nextIndexPair);
	}
	else
	{
		onGround = false;
	}
	//落ち終わった後のポジションが地面の上だったら
	if (falledPositionY > nextPosition && onGround)
	{
		playerMoveAmount.y = (nextPosition - falledPositionY);
		return new NoActionState();
	}
	else if (falledPositionY == nextPosition && onGround)
	{
		playerMoveAmount.y = -fallSpeed;
		return new NoActionState();
	}
	else
	{
		if (onGround)
		{
			actionManager.AttackEnemy(nextIndexPair, player);
		}
		playerMoveAmount.y = -fallSpeed;
		if (playerExactlyPosition.y - (BLOCK_SIZE / 2) > nextPosition)
		{
			actionManager.AttackEnemy(nextIndexPair, player);
		}
	}
	return this;
}

