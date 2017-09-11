#ifndef CALCULATE_RUNNING_DIRECCTION_H
#define CALCULATE_RUNNING_DIRECCTION_H

#include "SelfPositionChecker.h"

namespace unit
{
	class CalculateRunningDirection{
	private:
		int mState;
		SelfPositionChecker* mSelfPositionChecker;

	public:
		CalculateRunningDirection(SelfPositionChecker* selfPositionChecker);
		~CalculateRunningDirection();

		int calculate();
	};


}


#endif
