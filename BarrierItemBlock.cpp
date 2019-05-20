//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#include "Common.h"
#include "BlockBase.h"
#include "BarrierItemBlock.h"
#include "EffectCreater.h"
#include "SoundManager.h"
#include "Player.h"

BarrierItemBlock::BarrierItemBlock(int sourceModelHandle, VECTOR startPos)
	:BlockBase(sourceModelHandle, startPos)
{
	blockName = BLOCK;
	playingHandle = effect->PlayItemEffect(pos);
	playingHandleBlock = effect->CreateBarrierItemEffect(pos);
	MV1DeleteModel(modelHandle);
}

BarrierItemBlock::~BarrierItemBlock()
{
	effect->StopEffect(playingHandle);
	effect->StopEffect(playingHandleBlock);
	MV1DeleteModel(modelHandle);
}

void BarrierItemBlock::Update()
{
	MV1SetPosition(modelHandle, pos);
}

void BarrierItemBlock::Attacked(Player & player)
{
	//effect->CreateBreakBlockEffect(pos);
	soundManager->PlayStoneBreak();
	//MV1DeleteModel(modelHandle);
	active = false;
	player.BarrierItemGet();
	effect->StopEffect(playingHandle);
	effect->StopEffect(playingHandleBlock);
}

void BarrierItemBlock::OnBlock(Player & player)
{
}
