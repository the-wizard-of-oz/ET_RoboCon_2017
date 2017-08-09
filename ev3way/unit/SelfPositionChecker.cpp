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
		// 現状ではeBlackかeWhiteしか返ってこないため、ゴールしたと判定されることはない。
		return (mColorJudge->judgeLineColor() == unit::eGlay);
	}

	bool SelfPositionChecker::isOnBlackLine()
	{
		return (mColorJudge->judgeLineColor() == unit::eBlack);
	}
}  // namespace unit
