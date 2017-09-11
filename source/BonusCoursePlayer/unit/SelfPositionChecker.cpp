#include "SelfPositionChecker.h"

namespace unit
{
	SelfPositionChecker::SelfPositionChecker(ColorJudge* colorJudge)
	: mColorJudge(colorJudge)
	{
	}
	
	SelfPositionChecker::~SelfPositionChecker()
	{
		mColorJudge = nullptr;
	}

	bool SelfPositionChecker::reachedGoal()
	{
		return false;
	}

	bool SelfPositionChecker::isOnBlackLine()
	{
		return (mColorJudge->judgeLineColor() == unit::eBlack);
	}
}  // namespace unit
