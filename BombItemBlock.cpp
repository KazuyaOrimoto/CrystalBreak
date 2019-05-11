//-----------------------------------------------------------------------------//
//						必要なライブラリのインクルード
//-----------------------------------------------------------------------------//
#include "Common.h"
#include "BlockBase.h"
#include "BombItemBlock.h"
#include "EffectCreater.h"
#include "SoundManager.h"
#include "Player.h"

BombItemBlock::BombItemBlock(int sourceModelHandle, VECTOR startPos)
	:BlockBase(sourceModelHandle, startPos)
{
	blockName = BLOCK;
	playingHandle = effect->PlayItemEffect(pos);
	playingHandleBlock = effect->CreateBombItemEffect(pos);
}

BombItemBlock::~BombItemBlock()
{
	effect->StopEffect(playingHandle);
	effect->StopEffect(playingHandleBlock);
	MV1DeleteModel(modelHandle);

}

void BombItemBlock::Update()
{
	MV1SetPosition(modelHandle, pos);
}

void BombItemBlock::Attacked(Player & player)
{
	//effect->CreateBreakBlockEffect(pos);
	soundManager->PlayStoneBreak();
	MV1DeleteModel(modelHandle);
	active = false;
	player.BombItemGet();
	effect->StopEffect(playingHandle);
	effect->StopEffect(playingHandleBlock);
}

void BombItemBlock::OnBlock(Player & player)
{

}
