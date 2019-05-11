//-----------------------------------------------------------------------------//
//						必要なライブラリのインクルード
//-----------------------------------------------------------------------------//
#include "Common.h"
#include "BlockBase.h"
#include "FireBlock.h"
#include "EffectCreater.h"
#include "SoundManager.h"
#include "Player.h"

//-----------------------------------------------------------------------------//
//								コンストラクタ
//-----------------------------------------------------------------------------//
FireBlock::FireBlock(int sourceModelHandle, VECTOR startPos, Direction dir)
	:BlockBase(sourceModelHandle, startPos)
{
	blockName = FIRE_CUBE;
	if (dir == RIGHT)
	{
		MV1SetRotationXYZ(modelHandle,VGet(0.0f, DX_PI_F,0.0f));
	}
}

//-----------------------------------------------------------------------------//
//								デストラクタ
//-----------------------------------------------------------------------------//
FireBlock::~FireBlock()
{
	MV1DeleteModel(modelHandle);

}

//-----------------------------------------------------------------------------//
//								アップデート処理
//-----------------------------------------------------------------------------//
void FireBlock::Update()
{
	MV1SetPosition(modelHandle, pos);
}

//-----------------------------------------------------------------------------//
//								攻撃されたときの処理
//-----------------------------------------------------------------------------//
void FireBlock::Attacked(Player & player)
{
	effect->CreateFireBlockBreakEffect(pos);
	soundManager->PlayStoneBreak();
	MV1DeleteModel(modelHandle);
	active = false;
}

void FireBlock::OnBlock(Player& player)
{
}
