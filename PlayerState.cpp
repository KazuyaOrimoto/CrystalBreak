#include "Common.h"
#include "PlayerState.h"
#include "InputMAnager.h"
#include "Stage.h"
#include "ActionManager.h"
#include "NoActionState.h"
#include "Player.h"
#include "SoundManager.h"
#include "EffectCreater.h"

PlayerState::PlayerState()
{
	ResetAmount();
	soundManager = SoundManager::GetInstance();
	effectCreater = EffectCreater::GetInstance();
	previewDirection = RIGHT;
}

PlayerState::~PlayerState()
{
}


PlayerState * PlayerState::InitPlayerState()
{
	PlayerState* state =new NoActionState();
	state->SetRotation(VECTOR_ZERO);
	return state;
}

VECTOR PlayerState::GetMoveAmount()
{
	return playerMoveAmount;
}

VECTOR PlayerState::GetRotation()
{
	return playerRotation;
}

VECTOR PlayerState::GetScaleAmount()
{
	return playerScaleAmount;
}

VECTOR PlayerState::GetAnimationPosition()
{
	return playerAnimationPosition;
}

Direction PlayerState::GetDirecion()
{
	return previewDirection;
}

void PlayerState::SetRotation(VECTOR rotation)
{
	playerRotation = rotation;
}

void PlayerState::passPreviewDirection(Direction dir)
{
	previewDirection = dir;
}

void PlayerState::ResetAmount()
{
	playerMoveAmount = VECTOR_ZERO;
	playerRotation = playerRotation;
	playerScaleAmount = VECTOR_ZERO;
	playerAnimationPosition = VECTOR_ZERO;
}
