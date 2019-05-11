//-----------------------------------------------------------------------------//
//						必要なライブラリのインクルード
//-----------------------------------------------------------------------------//
#include "Common.h"
#include "BlockBase.h"
#include "Sphere.h"
#include "EffectCreater.h"
#include "SoundManager.h"

//-----------------------------------------------------------------------------//
//								コンストラクタ
//-----------------------------------------------------------------------------//
BlockBase::BlockBase(int sourceModelHandle, VECTOR startPos)
{
	modelHandle = MV1DuplicateModel(sourceModelHandle);
	MV1SetScale(modelHandle, VGet(BLOCK_MAGNIFICATION_RATE, BLOCK_MAGNIFICATION_RATE, BLOCK_MAGNIFICATION_RATE));
	pos = startPos;
	active = true;
	indexPair = { int(pos.x / BLOCK_SIZE) ,int(pos.y / -BLOCK_SIZE) };
	collisionSphere = new Sphere();
	collisionSphere->radius = BLOCK_MAGNIFICATION_RATE;
	collisionSphere->centerPos = pos;
	effect = EffectCreater::GetInstance();
	soundManager = SoundManager::GetInstance();
}

//-----------------------------------------------------------------------------//
//								デストラクタ
//-----------------------------------------------------------------------------//
BlockBase::~BlockBase()
{
	delete(collisionSphere);
	MV1DeleteModel(modelHandle);
}

//-----------------------------------------------------------------------------//
//								描画処理
//-----------------------------------------------------------------------------//
void BlockBase::Draw()
{
	if (needDrawModel(pos))
	{
		MV1SetPosition(modelHandle,pos);
		MV1DrawModel(modelHandle);
	}
}

//-----------------------------------------------------------------------------//
//								ブロックの名前を渡す
//-----------------------------------------------------------------------------//
BlockName BlockBase::GetBlockName()
{
	if (!active)
	{
		return NO_BLOCK;
	}
	return blockName;
}

//-----------------------------------------------------------------------------//
//								アクティブかどうか
//-----------------------------------------------------------------------------//
bool BlockBase::IsActive()
{
	return active;
}

//-----------------------------------------------------------------------------//
//								要素位置を渡す
//-----------------------------------------------------------------------------//
IndexPair BlockBase::GetIndexPair()
{
	return indexPair;
}

//-----------------------------------------------------------------------------//
//								ポジションを渡す
//-----------------------------------------------------------------------------//
VECTOR BlockBase::GetPosition()
{
	return pos;
}

Sphere& BlockBase::GetCollisionSphere()
{
	return *collisionSphere;
}

void BlockBase::NextStageCreate()
{
	pos.y += NEXT_STAGE_CREATE_ADD_POSITION;
}

bool BlockBase::needDrawModel(VECTOR position)
{
	VECTOR boxPos1 = VGet(position.x + MAGNIFICATION_RATE, position.y + MAGNIFICATION_RATE, position.z + MAGNIFICATION_RATE);
	VECTOR boxPos2 = VGet(position.x - MAGNIFICATION_RATE, position.y - MAGNIFICATION_RATE, position.z - MAGNIFICATION_RATE);
	bool needDraw = CheckCameraViewClip_Box(boxPos1, boxPos2);
	return !needDraw;
}
