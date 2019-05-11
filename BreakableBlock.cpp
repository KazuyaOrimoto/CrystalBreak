//-----------------------------------------------------------------------------//
//						必要なライブラリのインクルード
//-----------------------------------------------------------------------------//
#include "Common.h"
#include "BlockBase.h"
#include "BreakableBlock.h"
#include "EffectCreater.h"
#include "SoundManager.h"

//-----------------------------------------------------------------------------//
//								コンストラクタ
//-----------------------------------------------------------------------------//
BreakableBlock::BreakableBlock(int sourceModelHandle, VECTOR startPos)
	:BlockBase(sourceModelHandle, startPos)
{
	blockName = BLOCK;
}

//-----------------------------------------------------------------------------//
//								デストラクタ
//-----------------------------------------------------------------------------//
BreakableBlock::~BreakableBlock()
{
	MV1DeleteModel(modelHandle);

}

//-----------------------------------------------------------------------------//
//								アップデート処理
//-----------------------------------------------------------------------------//
void BreakableBlock::Update()
{
	MV1SetPosition(modelHandle, pos);
}

//-----------------------------------------------------------------------------//
//								攻撃されたときの処理
//-----------------------------------------------------------------------------//
void BreakableBlock::Attacked(Player & player)
{
	effect->CreateBreakBlockEffect(pos);
	soundManager->PlayStoneBreak();
	MV1DeleteModel(modelHandle);
	active = false;
}

void BreakableBlock::OnBlock(Player& player)
{
}
