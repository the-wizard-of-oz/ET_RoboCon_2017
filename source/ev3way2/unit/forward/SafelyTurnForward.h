#ifndef UNIT_SAFELY_TURN_FORWARD_H
#define UNIT_SAFELY_TURN_FORWARD_H

#include "IForward.h"
#include "ITurn.h"

namespace unit
{
	static const int RIGHT_TURN_LIMIT_DEFAULT =  10;
	static const int LEFT_TURN_LIMIT_DEFAULT  = -10;
	static const int LIMITED_FORWARD_DEFAULT  =  15;
	
	class SafelyTurnForward
	: public IForward
	{
	//
	private:
		ITurn* mITurn;
		int mTargetForward;
		int mLimitedForward;
		int mRightTurnLimit;
		int mLeftTurnLimit;
	
	//
	public:
		SafelyTurnForward();
		SafelyTurnForward(ITurn* iTurn,
						  int targetForward  = LIMITED_FORWARD_DEFAULT,
						  int limitedForward = LIMITED_FORWARD_DEFAULT,
						  int rightTurnLimit = RIGHT_TURN_LIMIT_DEFAULT,
						  int leftTurnLimit  = LEFT_TURN_LIMIT_DEFAULT);
		virtual ~SafelyTurnForward();

		virtual int calculateForward();
	};
}  // namespace unit
#endif
