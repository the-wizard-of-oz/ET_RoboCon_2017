#ifndef UNIT_DEBUGSTARTER_H
#define UNIT_DEBUGSTARTER_H

#include "unit/PostureController.h"
#include "unit/StartMonitor.h"
#include "unit/BalancingRunner.h"
#include "unit/BalancingRunnerZERO.h"
#include "unit/DistanceMeter.h"
#include "unit/MotorController.h"

#define INITIALIZE 0
#define WAIT 1
#define GO 2
#define DONE 3

#define ZEROYON 10
#define STOP 11
#define REDUCE 12
#define ZEROYON_START 13

#define RUNNING_DISTANCE 4000
#define REDUCE_DISTANCE 100

namespace unit
{
	class DebugStarter
	{
	private:
		PostureController* mTailController;
		StartMonitor* mStartMonitor;
		BalancingRunner* mBalancingRunner;
		BalancingRunnerZERO* mBalancingRunnerZERO;
		DistanceMeter* mDistanceMeter;
		MotorController* mMotorController;
		int mState;

	public:
		DebugStarter(PostureController* tailController, StartMonitor* startMonitor, BalancingRunner* balancingRunner, BalancingRunnerZERO* balancingRunnerZERO, DistanceMeter* distanceMeter, MotorController* motorController);
		~DebugStarter();
		bool execute();
	};
}  // namespace unit
#endif
