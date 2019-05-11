#include "Common.h"
#include "PlayerState.h"
#include "NoActionState.h"
#include "UpAttackState.h"
#include "InputMAnager.h"
#include "Stage.h"
#include "Player.h"
#include "EffectCreater.h"
#include "SoundManager.h"
#include "ActionManager.h"

UpAttackState::UpAttackState()
{
	animationCount = 0;
}

UpAttackState::~UpAttackState()
{
}

PlayerState * UpAttackState::Update(Player & player, Stage & stage, InputManager & inputManager, ActionManager& actionManager)
{
	ResetAmount();

	animationCount++;
	//アニメーションを始めて15フレーム未満なら
	if (15 > animationCount)
	{
		playerScaleAmount.y = -PLAYER_SCALE_AMOUNT / 2.0;
		playerAnimationPosition.y = -PLAYER_SCALE_AMOUNT * animationCount / 2.0f;
	}
	else
	{
		soundManager->PlayPlayerAttack();

		effectCreater->CreateUpperAttackEffect(player.GetPosition());
		IndexPair indexPairUp = player.GetIndexPair().IndexPairUp();
		stage.BreakBlock(indexPairUp, player);
		actionManager.AttackEnemy(indexPairUp, player);
		playerScaleAmount.y = PLAYER_SCALE_AMOUNT * 7.0;
		return new NoActionState();
	}

	return this;
}
