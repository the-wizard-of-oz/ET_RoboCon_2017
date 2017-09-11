#include "CalculateRunningDirection.h"
#include "SelfPositionChecker.h"

namespace unit
{
	CalculateRunningDirection::CalculateRunningDirection(SelfPositionChecker* selfPositionChecker)
	:mSelfPositionChecker(selfPositionChecker)
	{

	}
	CalculateRunningDirection::~CalculateRunningDirection()
	{

	}

	int CalculateRunningDirection::calculate()
	{
		int direction = 0;
		// 左エッジ走行するよう設定
		if (mSelfPositionChecker->isOnBlackLine())
		{
			direction = -1;
		}
		else
		{
			direction = 1;
		}
		return direction;
	}
}
