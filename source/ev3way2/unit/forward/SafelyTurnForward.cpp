#include "SafelyTurnForward.h"

namespace unit
{
	SafelyTurnForward::SafelyTurnForward()
	: IForward(), mITurn(nullptr), mTargetForward(LIMITED_FORWARD_DEFAULT), mLimitedForward(LIMITED_FORWARD_DEFAULT),
	  mRightTurnLimit(RIGHT_TURN_LIMIT_DEFAULT), mLeftTurnLimit(LEFT_TURN_LIMIT_DEFAULT)
	{
	}
	
	SafelyTurnForward::SafelyTurnForward(ITurn* iTurn,
										 int targetForward,
										 int limitedForward,
										 int rightTurnLimit,
										 int leftTurnLimit)
	: IForward(), mITurn(iTurn), mTargetForward(targetForward), mLimitedForward(limitedForward),
	  mRightTurnLimit(rightTurnLimit), mLeftTurnLimit(leftTurnLimit)
	{
	}
	
	SafelyTurnForward::~SafelyTurnForward()
	{
		mITurn = nullptr;
	}
	
	int SafelyTurnForward::calculateForward()
	{
		int forward = 0;
		
		if(mITurn != nullptr)
		{
			forward = mTargetForward;
			bool needUpdate = false;
			int turn = mITurn->getTurn(needUpdate);
			if(turn < mLeftTurnLimit)  forward = mLimitedForward;
			if(turn > mRightTurnLimit) forward = mLimitedForward;
		}
		
		return forward;
	}
}  // namespace unit
