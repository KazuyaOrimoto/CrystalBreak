#include "Common.h"
#include "PlayerState.h"
#include "SwallowDarkState.h"
#include "InputMAnager.h"
#include "Stage.h"
#include "Player.h"
#include "NoActionState.h"
#include "ActionManager.h"
#include "SoundManager.h"

SwallowDarkState::SwallowDarkState(VECTOR position)
{
	swallowPosition = position;
}

SwallowDarkState::~SwallowDarkState()
{
}

PlayerState * SwallowDarkState::Update(Player & player, Stage & stage, InputManager & inputManager, ActionManager & actionManager)
{
	playerRotation = player.GetRotation();
	playerRotation.x += (RANDOM_LOWEST + GetRand(RANDOM_LIMIT)) * DX_PI_F / SEMICIRCLE;
	playerRotation.x += (RANDOM_LOWEST + GetRand(RANDOM_LIMIT)) * DX_PI_F / SEMICIRCLE;
	playerRotation.x += (RANDOM_LOWEST + GetRand(RANDOM_LIMIT)) * DX_PI_F / SEMICIRCLE;

	playerScaleAmount.x = DECREASE_SIZE_NUM;
	playerScaleAmount.y = DECREASE_SIZE_NUM;
	playerScaleAmount.z = DECREASE_SIZE_NUM;

	VECTOR playerMoveNum = VSub(swallowPosition, player.GetPosition());
	playerMoveAmount.x = playerMoveNum.x * FACTOR_NUM;
	playerMoveAmount.y = playerMoveNum.y * FACTOR_NUM;
	playerMoveAmount.z = playerMoveNum.z * FACTOR_NUM;

	swallowCount++;

	if (swallowCount > SWALLOW_END_COUNT)
	{
		soundManager->PlayLaugh();
		player.PlayerDie();
		return new NoActionState();
	}
	return this;
}
