#include "Common.h"
#include "PlayerState.h"
#include "ExplosionState.h"
#include "InputMAnager.h"
#include "Stage.h"
#include "Player.h"
#include "NoActionState.h"
#include "ActionManager.h"
#include "SoundManager.h"
#include "EffectCreater.h"

ExplosionState::ExplosionState()
{
	effectCteateCount = 0;
}

ExplosionState::~ExplosionState()
{
}

PlayerState * ExplosionState::Update(Player & player, Stage & stage, InputManager & inputManager, ActionManager & actionManager)
{
	playerScaleAmount.x = DECREASE_SIZE_NUM;
	playerScaleAmount.y = DECREASE_SIZE_NUM;
	playerScaleAmount.z = DECREASE_SIZE_NUM;
	effectCteateCount++;
	if (effectCteateCount > EFFECT_START_COUNT)
	{
		soundManager->PlayPlayerExplosion();
		effectCreater->CreatePlayerExplosionEffect(player.GetPosition());
		player.PlayerDie();
		return new NoActionState();
	}

	return this;
}
