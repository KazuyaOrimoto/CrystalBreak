#include "Common.h"
#include "PlayerState.h"
#include "RightMoveState.h"
#include "InputMAnager.h"
#include "Stage.h"
#include "Player.h"
#include "NoActionState.h"

RightMoveState::RightMoveState()
	: PlayerState()
{
	animationCount = 0;
}

RightMoveState::~RightMoveState()
{
}

PlayerState * RightMoveState::Update(Player& player, Stage & stage, InputManager & inputManager, ActionManager& actionManager)
{
	ResetAmount();
	
	Animation();
	VECTOR playerPosition = player.GetPosition();
	VECTOR playerExactlyPosition = player.GetExactlyPosition();
	float rightMovedPositionX = playerExactlyPosition.x + BLOCK_SIZE;
	float nextPosition = playerPosition.x + PLAYER_MOVE_SPEED;
	if (rightMovedPositionX < nextPosition)
	{
		playerMoveAmount.x = nextPosition - rightMovedPositionX;
		return new NoActionState();
	}
	else if (rightMovedPositionX == nextPosition)
	{
		playerMoveAmount.x = PLAYER_MOVE_SPEED;
		return new NoActionState();
	}
	else
	{
		playerMoveAmount.x = PLAYER_MOVE_SPEED;
	}

	return this;
}

void RightMoveState::Animation()
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
