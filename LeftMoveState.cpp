//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#include "Common.h"
#include "PlayerState.h"
#include "LeftMoveState.h"
#include "InputMAnager.h"
#include "Stage.h"
#include "Player.h"
#include "NoActionState.h"


LeftMoveState::LeftMoveState()
	: PlayerState()
{
	needSavePreviw = true;
	animationCount = 0;
}

LeftMoveState::~LeftMoveState()
{
}

PlayerState * LeftMoveState::Update(Player& player, Stage& stage, InputManager& inputManager, ActionManager& actionManager)
{
	ResetAmount();
	if (needSavePreviw)
	{
		previewPlayerPosition = player.GetExactlyPosition();
		needSavePreviw = false;
	}
	Animation();
	VECTOR playerPosition = player.GetPosition();
	float leftMovedPositionX = previewPlayerPosition.x - BLOCK_SIZE;
	float nextPosition = playerPosition.x - PLAYER_MOVE_SPEED;
	if (leftMovedPositionX > nextPosition)
	{
		playerMoveAmount.x = nextPosition - leftMovedPositionX;
		return new NoActionState();
	}
	else if (leftMovedPositionX == nextPosition)
	{
		playerMoveAmount.x = -PLAYER_MOVE_SPEED;
		return new NoActionState();
	}
	else
	{
		playerMoveAmount.x = -PLAYER_MOVE_SPEED;
	}
	return this;
}

void LeftMoveState::Animation()
{
	animationCount++;
	if (animationCount <= 5)
	{
		playerScaleAmount = VGet(0.0f, -PLAYER_SCALE_AMOUNT, 0.0f);
		playerAnimationPosition.y = -PLAYER_SCALE_AMOUNT;
	}
	else if (animationCount <= 10)
	{
		playerScaleAmount = VGet(0.0f, PLAYER_SCALE_AMOUNT, 0.0f);
		playerAnimationPosition.y = PLAYER_SCALE_AMOUNT;
	}
}