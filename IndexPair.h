#pragma once

struct IndexPair
{
	int x;
	int y;
	bool operator < (const IndexPair& value) const
	{
		int compareNum = x * 100 + y;
		int conpareValue = value.x * 100 + value.y;
		if (compareNum < conpareValue)
		{
			return true;
		}
		else
		{
			return false;
		}
		return false;
	}

	IndexPair IndexPairRight()
	{
		IndexPair right = { x + 1 ,y };
		return right;
	}
	IndexPair IndexPairLeft()
	{
		IndexPair left = { x - 1 ,y };
		return left;
	}
	IndexPair IndexPairUp()
	{
		IndexPair up = { x ,y - 1 };
		return up;
	}
	IndexPair IndexPairDown()
	{
		IndexPair down = { x  ,y + 1 };
		return down;
	}
};