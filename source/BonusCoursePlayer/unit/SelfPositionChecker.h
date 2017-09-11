#ifndef UNIT_SELF_POSITION_CHECKER_H
#define UNIT_SELF_POSITION_CHECKER_H

#include "ColorJudge.h"

namespace unit
{
	class SelfPositionChecker
	{
	private:
		bool mIsExistingOnLine;
		ColorJudge* mColorJudge;

	public:
		SelfPositionChecker(ColorJudge* colorJudge);
		~SelfPositionChecker();
		bool reachedGoal();
		bool isOnBlackLine();
	};
}  // namespace unit
#endif
