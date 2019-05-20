//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#include "Common.h"
#include "BlockBase.h"
#include "SharpBlock.h"
#include "EffectCreater.h"
#include "SoundManager.h"
#include "Player.h"

SharpBlock::SharpBlock(int sourceModelHandle, VECTOR startPos)
	:BlockBase(sourceModelHandle, startPos)
{
	blockName = SHARP_BLOCK;
}

SharpBlock::~SharpBlock()
{
	MV1DeleteModel(modelHandle);

}

void SharpBlock::Update()
{
	MV1SetPosition(modelHandle, pos);
}

void SharpBlock::Attacked(Player & player)
{
	effect->CreateBreakBlockEffect(pos);
	soundManager->PlayStoneBreak();
	MV1DeleteModel(modelHandle);
	active = false;
}

void SharpBlock::OnBlock(Player& player)
{
	player.Attacked();
}
