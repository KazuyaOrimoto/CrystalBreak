//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//
#include "Common.h"
#include "EnemyBase.h"
#include "ActionManager.h"
#include "Score.h"
#include "Sphere.h"
#include "SoundManager.h"
#include "EffectCreater.h"
#include "Player.h"

//-----------------------------------------------------------------------------//
//								コンストラクタ
//-----------------------------------------------------------------------------//
EnemyBase::EnemyBase(int sourceModelHandle, VECTOR startPos, ActionManager &actionManager,int addPoint)
	:addPoint(addPoint)
{
	modelHandle = MV1DuplicateModel(sourceModelHandle);
	MV1SetScale(modelHandle, VGet(MAGNIFICATION_RATE, MAGNIFICATION_RATE, MAGNIFICATION_RATE));
	position = startPos;
	exactlyPosition = position;
	actionManager.InsertEnemyIndexPair(this, indexPair);
	ChangeEnemyIndexPair(actionManager);
	score = Score::GetInstance();
	collisionSphere = new Sphere();
	collisionSphere->centerPos = position;
	collisionSphere->radius = MAGNIFICATION_RATE / 2;
	soundManager = SoundManager::GetInstance();
	effectCreater = EffectCreater::GetInstance();
}

//-----------------------------------------------------------------------------//
//								デストラクタ
//-----------------------------------------------------------------------------//
EnemyBase::~EnemyBase()
{
	delete(collisionSphere);
	MV1DeleteModel(modelHandle);
}

//-----------------------------------------------------------------------------//
//								描画処理
//-----------------------------------------------------------------------------//
void EnemyBase::Draw()
{
	MV1SetPosition(modelHandle,position);
	MV1DrawModel(modelHandle);
}

//-----------------------------------------------------------------------------//
//								攻撃されたとき
//-----------------------------------------------------------------------------//
EnemyBase* EnemyBase::Attacked(Player& player)
{
	MV1DeleteModel(modelHandle);
	score->AddScore(addPoint);
	isAlive = false;
	DieEffect();
	return this;
}

bool EnemyBase::isActive()
{
	return isAlive;
}

IndexPair EnemyBase::GetIndexPair()
{
	return indexPair;
}

Sphere& EnemyBase::GetCollisionSphere()
{
	return *collisionSphere;
}

VECTOR EnemyBase::GetPosition()
{
	return position;
}

bool EnemyBase::IsAttacking()
{
	return attackFlag;
}

void EnemyBase::NextStageCreate()
{
	position.y += NEXT_STAGE_CREATE_ADD_POSITION;
}

//-----------------------------------------------------------------------------//
//								要素位置の変更
//-----------------------------------------------------------------------------//
void EnemyBase::ChangeEnemyIndexPair(ActionManager & actionManager)
{
	indexPair = { int(exactlyPosition.x / BLOCK_SIZE) ,int(exactlyPosition.y / -BLOCK_SIZE) };
	actionManager.SetEnemyIndexPair(this, indexPair);
	needChangeIndex = false;
}
