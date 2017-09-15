#ifndef UNIT_SAFELY_TURN_FORWARD_H
#define UNIT_SAFELY_TURN_FORWARD_H

#include "IForward.h"
#include "ITurn.h"

namespace unit
{
	static const float RIGHT_TURN_LIMIT_DEFAULT =  10.f;
	static const float LEFT_TURN_LIMIT_DEFAULT  = -10.f;
	static const float LIMITED_FORWARD_DEFAULT  =  15.f;
	
	class SafelyTurnForward
	: public IForward
	{
	//
	private:
		ITurn* mITurn;
		float mTargetForward;
		float mLimitedForward;
		float mRightTurnLimit;
		float mLeftTurnLimit;
	
	//
	public:
		SafelyTurnForward();
		SafelyTurnForward(ITurn* iTurn,
						  float targetForward  = LIMITED_FORWARD_DEFAULT,
						  float limitedForward = LIMITED_FORWARD_DEFAULT,
						  float rightTurnLimit = RIGHT_TURN_LIMIT_DEFAULT,
						  float leftTurnLimit  = LEFT_TURN_LIMIT_DEFAULT);
		virtual ~SafelyTurnForward();

		virtual float calculateForward();
	};
}  // namespace unit
#endif
