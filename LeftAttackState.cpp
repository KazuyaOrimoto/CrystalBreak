//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#include "Common.h"
#include "PlayerState.h"
#include "NoActionState.h"
#include "LeftAttackState.h"
#include "InputMAnager.h"
#include "Stage.h"
#include "Player.h"
#include "EffectCreater.h"
#include "SoundManager.h"
#include "ActionManager.h"


LeftAttackState::LeftAttackState()
{
	animationCount = 0;
}


LeftAttackState::~LeftAttackState()
{
}

PlayerState * LeftAttackState::Update(Player & player, Stage & stage, InputManager & inputManager, ActionManager & actionManager)
{
	ResetAmount();

	animationCount++;
	//アニメーションを始めて15フレーム未満なら
	if (15 > animationCount)
	{
		playerScaleAmount.y = PLAYER_SCALE_AMOUNT / 4.0f;
		playerAnimationPosition.y = PLAYER_SCALE_AMOUNT * animationCount / 4.0f;
	}
	else
	{
		soundManager->PlayPlayerAttack();

		effectCreater->CreateLeftAttackEffect(player.GetExactlyPosition());
		IndexPair indexPairLeft = player.GetIndexPair().IndexPairLeft();
		stage.BreakBlock(indexPairLeft, player);
		actionManager.AttackEnemy(indexPairLeft, player);
		playerScaleAmount.y = -PLAYER_SCALE_AMOUNT * 3.5f;
		return new NoActionState();
	}

	return this;
}
