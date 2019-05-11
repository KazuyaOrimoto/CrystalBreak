#include "Common.h"
#include "BackGround.h"

BackGround::BackGround(int sorceModelHandle, VECTOR positionValue)
{
	modelHandle = MV1DuplicateModel(sorceModelHandle);
	MV1SetScale(modelHandle, VGet(MAGNIFICATION_RATE, MAGNIFICATION_RATE, MAGNIFICATION_RATE));
	MV1SetPosition(modelHandle, positionValue);
	position = positionValue;
}

BackGround::~BackGround()
{
}

void BackGround::Draw()
{
	MV1DrawModel(modelHandle);
}

void BackGround::NextStageCreate()
{
	position.y += NEXT_STAGE_CREATE_ADD_POSITION;
	MV1SetPosition(modelHandle, position);
}
