#include "Common.h"
#include "PlayerState.h"
#include "NoActionState.h"
#include "DownAttackState.h"
#include "InputMAnager.h"
#include "Stage.h"
#include "Player.h"
#include "EffectCreater.h"
#include "SoundManager.h"
#include "ActionManager.h"


DownAttackState::DownAttackState()
{
	animationCount = 0;
}


DownAttackState::~DownAttackState()
{
}

PlayerState * DownAttackState::Update(Player & player, Stage & stage, InputManager & inputManager, ActionManager & actionManager)
{
	ResetAmount();

	animationCount++;
	//アニメーションを始めて15フレーム未満なら
	if (15 > animationCount)
	{
		playerScaleAmount.y = -PLAYER_SCALE_AMOUNT / 2.0;
		//playerAnimationPosition.y = -PLAYER_SCALE_AMOUNT * animationCount / 2.0f;
	}
	else
	{
		soundManager->PlayPlayerAttack();

		effectCreater->CreateUnderAttackEffect(player.GetPosition());
		IndexPair indexPairDown = player.GetIndexPair().IndexPairDown();
		stage.BreakBlock(indexPairDown, player);
		actionManager.AttackEnemy(indexPairDown, player);
		playerScaleAmount.y = PLAYER_SCALE_AMOUNT * 7.0;
		return new NoActionState();
	}

	return this;
}
