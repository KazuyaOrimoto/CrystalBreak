//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#include "Common.h"
#include "EnemyBase.h"
#include "Boar.h"
#include "ActionManager.h"
#include "Stage.h"
#include "Sphere.h"
#include "SoundManager.h"
#include "EffectCreater.h"

//-----------------------------------------------------------------------------//
//								コンストラクタ
//-----------------------------------------------------------------------------//
Boar::Boar(int sourceModelHandle, VECTOR startPos, ActionManager &actionManager)
	:EnemyBase(sourceModelHandle, startPos, actionManager,550)
{
	exactlyPosition = position;
	rotation = MV1GetRotationXYZ(modelHandle);
	attackFlag = true;
}

//-----------------------------------------------------------------------------//
//								デストラクタ
//-----------------------------------------------------------------------------//
Boar::~Boar()
{
}

//-----------------------------------------------------------------------------//
//								アップデート処理
//-----------------------------------------------------------------------------//
void Boar::Update(Stage &stage, ActionManager &actionManager)
{
	Move(stage, actionManager);
	//要素位置の変更が必要なとき
	if (needChangeIndex)
	{
		ChangeEnemyIndexPair(actionManager);
		needChangeIndex = false;
	}
	//アクションの決定が必要な時
	if (actionFlag)
	{
		ActionDecision(actionManager);
	}

	MV1SetRotationXYZ(modelHandle, rotation);
	MV1SetPosition(modelHandle, position);

	collisionSphere->centerPos = position;
}

//-----------------------------------------------------------------------------//
//								移動処理
//-----------------------------------------------------------------------------//
void Boar::Move(Stage & stage, ActionManager& actionManager)
{
	if (isFalling)
	{
		Fall();
	}
	else if (needChangeDirection)
	{
		ChangeDirection();
	}
	else
	{
		if (isRightMoving)
		{
			RightMove();
		}
		else if (isLeftMoving)
		{
			LeftMove();
		}
		else if (rightAttackFlag)
		{
			DoRightAttack();
		}
		else if (leftAttackFlag)
		{
			DoLeftAttack();
		}
		else
		{
			DecisionMoveDirection(stage, actionManager);
		}
	}
}

//-----------------------------------------------------------------------------//
//								右移動処理
//-----------------------------------------------------------------------------//
void Boar::RightMove()
{
	if (animationCount < 20)
	{
		rotation.y = MOVE_RIGHT_ROTETION.y;
		rotation.z += 2.0f * DX_PI_F / 180.0f;
		animationCount++;
	}
	else
	{
		rotation.z -= 10.0f * DX_PI_F / 180.0f;
		float isRightMovedPositionX = exactlyPosition.x + BLOCK_SIZE;	//１マス分移動し終わったポジション
		MV1SetScale(modelHandle, VGet(MAGNIFICATION_RATE, MAGNIFICATION_RATE, MAGNIFICATION_RATE));
		VECTOR addPos = VGet(ENEMY_MOVE_SPEED, 0.0f, 0.0f);
		position = VAdd(position, addPos);
		position.y = exactlyPosition.y;
		if (isRightMovedPositionX <= position.x)
		{
			MoveEnd();
		}
	}
}

//-----------------------------------------------------------------------------//
//								左移動処理
//-----------------------------------------------------------------------------//
void Boar::LeftMove()
{
	if (animationCount < 20)
	{
		rotation.y = MOVE_LEFT_ROTETION.y;
		rotation.z -= 2.0f * DX_PI_F / 180.0f;
		animationCount++;
	}
	else
	{
		rotation.z += 10.0f * DX_PI_F / 180.0f;
		float isLeftMovedPositionX = exactlyPosition.x - BLOCK_SIZE;	//１マス分移動し終わったポジション
		MV1SetScale(modelHandle, VGet(MAGNIFICATION_RATE, MAGNIFICATION_RATE, MAGNIFICATION_RATE));
		VECTOR addPos = VGet(-ENEMY_MOVE_SPEED, 0.0f, 0.0f);
		position = VAdd(position, addPos);
		position.y = exactlyPosition.y;
		if (isLeftMovedPositionX >= position.x)
		{
			MoveEnd();
		}
	}
}

//-----------------------------------------------------------------------------//
//								移動終了処理
//-----------------------------------------------------------------------------//
void Boar::MoveEnd()
{
	isRightMoving = false;
	isLeftMoving = false;
	exactlyPosition = VGet((float)(int)(position.x / BLOCK_SIZE) * BLOCK_SIZE, (float)(int)(position.y / BLOCK_SIZE) * BLOCK_SIZE, (float)(int)(position.z / BLOCK_SIZE) * BLOCK_SIZE);
	position = exactlyPosition;
	needChangeIndex = true;
	actionFlag = false;
	animationCount = 0;
	rightAttackFlag = false;
	leftAttackFlag = false;
	isFalling = false;
}

//-----------------------------------------------------------------------------//
//								アクションを決める
//-----------------------------------------------------------------------------//
void Boar::ActionDecision(ActionManager & actionManager)
{
	actionFlag = false;
	action = actionManager.ReturnEnemyAction(this, moveDirection);
	if (action == ATTACK)
	{
		if (moveDirection == RIGHT)
		{
			rightAttackFlag = true;
			isRightMoving = false;
		}
		else if (moveDirection == LEFT)
		{
			leftAttackFlag = true;
			isLeftMoving = false;
		}
	}
}

//-----------------------------------------------------------------------------//
//								移動方向を決める
//-----------------------------------------------------------------------------//
void Boar::DecisionMoveDirection(Stage & stage, ActionManager& actionManager)
{
	if (!stage.CheckOnGround(indexPair))
	{
		isFalling = true;
		return;
	}
	//右移動をしているなら右を先に移動できるか調べる
	if (moveDirection == RIGHT)
	{
		//要素位置と進む方向を渡して移動可能か調べる
		if (stage.CanMove(indexPair, RIGHT))
		{
			//右が移動可能だったら右移動のフラグを立てる
			isRightMoving = true;
			moveDirection = RIGHT;
			actionManager.SetMoveEnemyIndexPair(this,indexPair.IndexPairRight());
		}
		//右に移動できなかった場合は左を調べる
		else
		{
			if (stage.CanMove(indexPair, LEFT))
			{
				//右が移動不可能で左が移動可能な場合は左移動のフラグを立てる
				isLeftMoving = true;
				needChangeDirection = true;
				moveDirection = LEFT;
				actionManager.SetMoveEnemyIndexPair(this, indexPair.IndexPairLeft());
			}
		}
	}
	//左移動をしているなら左を先に移動できるか調べる
	else if (moveDirection == LEFT)
	{
		//要素位置と進む方向を渡して移動可能か調べる
		if (stage.CanMove(indexPair, LEFT))
		{
			//左が移動可能だったらひだりの移動フラグを立てる
			isLeftMoving = true;
			moveDirection = LEFT;
			actionManager.SetMoveEnemyIndexPair(this, indexPair.IndexPairLeft());
		}
		//左に移動できなかった場合は右を調べる
		else
		{
			if (stage.CanMove(indexPair, RIGHT))
			{
				//左が移動不可能で右が移動可能な場合は右移動のフラグを立てる
				isRightMoving = true;
				needChangeDirection = true;
				moveDirection = RIGHT;
				actionManager.SetMoveEnemyIndexPair(this, indexPair.IndexPairRight());
			}
		}
	}
	actionFlag = true;
}

//-----------------------------------------------------------------------------//
//								落下処理
//-----------------------------------------------------------------------------//
void Boar::Fall()
{
	position.y -= ENEMY_FALL_SPEED;
	float nextExactlyPosition = exactlyPosition.y - BLOCK_SIZE;
	attackFlag = true;
	if (nextExactlyPosition >= position.y)
	{
		position.y = nextExactlyPosition;
		MoveEnd();
	}
}

void Boar::DieEffect()
{
	soundManager->PlayEnemyDie();
	effectCreater->CreateTakeCrystalEffect(position);
}

void Boar::DoRightAttack()
{
	if (animationCount < 20)
	{
		rotation.y = -80.0f * DX_PI_F / 180.0f;
		rotation.z += 2.0f * DX_PI_F / 180.0f;
		animationCount++;
	}
	else
	{
		attackFlag = true;
		rotation.z -= 10.0f * DX_PI_F / 180.0f;
		float isRightMovedPositionX = exactlyPosition.x + BLOCK_SIZE;	//１マス分移動し終わったポジション
		MV1SetScale(modelHandle, VGet(MAGNIFICATION_RATE, MAGNIFICATION_RATE, MAGNIFICATION_RATE));
		VECTOR addPos = VGet(ENEMY_MOVE_SPEED, 0.0f, 0.0f);
		position = VAdd(position, addPos);
		position.y = exactlyPosition.y;
		if (isRightMovedPositionX <= position.x)
		{
			attackFlag = false;
			MoveEnd();
		}
	}
}

void Boar::DoLeftAttack()
{
	if (animationCount < 20)
	{
		rotation.y = 80.0f * DX_PI_F / 180.0f;
		rotation.z -= 2.0f * DX_PI_F / 180.0f;
		animationCount++;
	}
	else
	{
		attackFlag = true;
		rotation.z += 10.0f * DX_PI_F / 180.0f;
		float isLeftMovedPositionX = exactlyPosition.x - BLOCK_SIZE;	//１マス分移動し終わったポジション
		MV1SetScale(modelHandle, VGet(MAGNIFICATION_RATE, MAGNIFICATION_RATE, MAGNIFICATION_RATE));
		VECTOR addPos = VGet(-ENEMY_MOVE_SPEED, 0.0f, 0.0f);
		position = VAdd(position, addPos);
		position.y = exactlyPosition.y;
		if (isLeftMovedPositionX >= position.x)
		{
			attackFlag = false;
			MoveEnd();
		}
	}
}

void Boar::ChangeDirection()
{
	if (needChangeDirection == false)
	{
		return;
	}

	if (moveDirection == RIGHT)
	{
		if (MV1GetRotationXYZ(modelHandle).y != MOVE_RIGHT_ROTETION.y)
		{
			rotation.y -= 10.0f * DX_PI_F / 180.0f;
			if (MV1GetRotationXYZ(modelHandle).y < MOVE_RIGHT_ROTETION.y)
			{
				rotation.y = MOVE_RIGHT_ROTETION.y;
			}
		}
		else
		{
			needChangeDirection = false;
		}
	}
	else if (moveDirection == LEFT)
	{
		if (MV1GetRotationXYZ(modelHandle).y != MOVE_LEFT_ROTETION.y)
		{
			rotation.y += 10.0f* DX_PI_F / 180.0f;
			if (MV1GetRotationXYZ(modelHandle).y > MOVE_LEFT_ROTETION.y)
			{
				rotation.y = MOVE_LEFT_ROTETION.y;
			}
		}
		else
		{
			needChangeDirection = false;
		}
	}
}
