﻿#include "Common.h"
#include "Capsule.h"

Capsule::Capsule()
{
	segment.startPos = VGet(0, 0, 0);
	segment.endPos = VGet(0, 1, 0);
	radius = 1.0f;
}