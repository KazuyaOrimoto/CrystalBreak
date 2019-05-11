#include "Common.h"
#include "BlockBase.h"
#include "CrumblyBlock.h"
#include "EffectCreater.h"
#include "SoundManager.h"

CrumblyBlock::CrumblyBlock(int sourceModelHandle, VECTOR startPos)
	:BlockBase(sourceModelHandle, startPos)
{
	blockName = BLOCK;
	breakToCount = 0;
}

CrumblyBlock::~CrumblyBlock()
{
	MV1DeleteModel(modelHandle);

}

void CrumblyBlock::Update()
{
	if (onRode)
	{
		float x = (float)GetRand(150);
		float y = (float)GetRand(150);
		float z = (float)GetRand(150);
		x = x / 200;
		y = y / 200;
		z = z / 200;
		breakToCount++;
		drawPos = VAdd(pos, VGet(x, y, z));
		MV1SetPosition(modelHandle, drawPos);
		if (breakToCount > CRUMBLY_TIME)
		{
			effect->CreateBreakBlockEffect(pos);
			soundManager->PlayStoneBreak();
			MV1DeleteModel(modelHandle);
			active = false;
		}
	}
	else
	{
		drawPos = pos;
		MV1SetPosition(modelHandle, pos);
	}
}

void CrumblyBlock::Attacked(Player & player)
{
	effect->CreateBreakBlockEffect(pos);
	soundManager->PlayStoneBreak();
	MV1DeleteModel(modelHandle);
	active = false;
}

void CrumblyBlock::OnBlock(Player& player)
{
	onRode = true;
}

void CrumblyBlock::Draw()
{
	if (needDrawModel(pos))
	{
		MV1SetPosition(modelHandle, drawPos);
		MV1DrawModel(modelHandle);
	}
}
