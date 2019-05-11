#include "Common.h"
#include "PlayerState.h"
#include "NoActionState.h"
#include "InputMAnager.h"
#include "Stage.h"
#include "RightMoveState.h"
#include "LeftMoveState.h"
#include "Player.h"
#include "FallState.h"
#include "SoundManager.h"
#include "UpAttackState.h"
#include "DownAttackState.h"
#include "RightAttackState.h"
#include "LeftAttackState.h"
#include "ActionManager.h"
#include "BombAttackState.h"
#include "SwallowDarkState.h"
#include "ExplosionState.h"

NoActionState::NoActionState()
	: PlayerState()
{
}

NoActionState::~NoActionState()
{
}

PlayerState * NoActionState::Update(Player& player, Stage& stage, InputManager& inputManager, ActionManager& actionManager)
{
	ResetAmount();
	//闇に飲まれているなら
	if (player.IsSwallowDark())
	{
		return new SwallowDarkState(player.GetSwallowPosition());
	}
	if (player.GetPlayerExplosion())
	{
		player.PlayExplosion();
		return new ExplosionState();
	}
	//プレイヤーが地面の上ならば
	if (player.GetPosition().y > 0)
	{
		return new FallState();
	}
	if (stage.CheckOnGround(player.GetIndexPair()))
	{
		if (player.CheckGameEnd())
		{
			return this;
		}
		stage.OnGroundStage(player.GetIndexPair(), player);
		if (inputManager.PlayerRightMove())
		{
			previewDirection = RIGHT;
			IndexPair nextIndexPair = player.GetIndexPair().IndexPairRight();
			if (stage.GetBlockName(nextIndexPair) == NO_BLOCK && actionManager.CanMovePlayer(nextIndexPair))
			{
				playerRotation = MOVE_RIGHT_ROTETION;
				soundManager->PlayPlayerMove();
				return new RightMoveState();
			}
		}
		if (inputManager.PlayerLeftMove())
		{
			previewDirection = LEFT;
			IndexPair nextIndexPair = player.GetIndexPair().IndexPairLeft();
			if (stage.GetBlockName(nextIndexPair) == NO_BLOCK && actionManager.CanMovePlayer(nextIndexPair))
			{
				playerRotation = MOVE_LEFT_ROTETION;
				soundManager->PlayPlayerMove();
				return new LeftMoveState();
			}
		}
		if (inputManager.PlayerUpAttack())
		{
			IndexPair nextIndexPair = player.GetIndexPair().IndexPairUp();
			if (stage.GetBlockName(nextIndexPair) != WALL)
			{
				playerRotation = VECTOR_ZERO;
				return new UpAttackState();
			}
		}
		if (inputManager.PlayerDownAttack())
		{
			IndexPair nextIndexPair = player.GetIndexPair().IndexPairDown();
			if (stage.GetBlockName(nextIndexPair) != WALL)
			{
				playerRotation = VECTOR_ZERO;
				return new DownAttackState();
			}
		}
		if (inputManager.PlayerRightAttack())
		{
			IndexPair nextIndexPair = player.GetIndexPair().IndexPairRight();
			if (stage.GetBlockName(nextIndexPair) != WALL)
			{
				previewDirection = RIGHT;
				playerRotation = MOVE_RIGHT_ROTETION;
				return new RightAttackState();

			}
		}
		if (inputManager.PlayerLeftAttack())
		{
			IndexPair nextIndexPair = player.GetIndexPair().IndexPairLeft();
			if (stage.GetBlockName(nextIndexPair) != WALL)
			{
				previewDirection = LEFT;
				playerRotation = MOVE_LEFT_ROTETION;
				return new LeftAttackState();
			}
		}
		if (inputManager.PlayerAttackOnly())
		{
			if (previewDirection == RIGHT)
			{
				IndexPair nextIndexPair = player.GetIndexPair().IndexPairRight();
				if (stage.GetBlockName(nextIndexPair) != WALL)
				{
					previewDirection = RIGHT;
					playerRotation = MOVE_RIGHT_ROTETION;
					return new RightAttackState();

				}
			}
			else if (previewDirection == LEFT)
			{
				IndexPair nextIndexPair = player.GetIndexPair().IndexPairLeft();
				if (stage.GetBlockName(nextIndexPair) != WALL)
				{
					previewDirection = LEFT;
					playerRotation = MOVE_LEFT_ROTETION;
					return new LeftAttackState();
				}
			}
		}
		if (inputManager.PlayerUseBomb())
		{
			if (player.CanUseBomb())
			{
				return new BombAttackState();
			}
		}
	}
	//プレイヤーが地面の上でなければ
	else
	{
		return new FallState();
	}

	return this;
}
