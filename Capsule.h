//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#pragma once

class Segment
{
public:
	VECTOR startPos;
	VECTOR endPos;
};

class Capsule
{
public:
	Segment segment;		//芯線
	float radius;			//半径
	Capsule();
};