//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#include "Common.h"
#include "PlayerState.h"
#include "NoActionState.h"
#include "BombAttackState.h"
#include "InputMAnager.h"
#include "Stage.h"
#include "Player.h"
#include "EffectCreater.h"
#include "SoundManager.h"
#include "ActionManager.h"


BombAttackState::BombAttackState()
{
	animationCount = 0;
	createdEffect = false;
}

BombAttackState::~BombAttackState()
{
}

PlayerState * BombAttackState::Update(Player & player, Stage & stage, InputManager & inputManager, ActionManager & actionManager)
{
	if (!createdEffect)
	{
		effectCreater->CreateBombEffect(player.GetPosition());
		createdEffect = true;
	}
	animationCount++;
	if (animationCount < 30)
	{
		return this;
	}
	else
	{
		IndexPair centerIndexPair = player.GetIndexPair();
		IndexPair serchIndex;
		for (int i = centerIndexPair.x - BOMB_BREAK_EIDTH_X; i < centerIndexPair.x + BOMB_BREAK_EIDTH_X + 1; i++)
		{
			for (int j = centerIndexPair.y - BOMB_BREAK_EIDTH_Y; j < centerIndexPair.y + BOMB_BREAK_EIDTH_Y + 1; j++)
			{
				serchIndex.x = i;
				serchIndex.y = j;
				stage.BreakBlock(serchIndex, player);
				actionManager.AttackEnemy(serchIndex, player);
			}
		}
		return new NoActionState();
	}
}
