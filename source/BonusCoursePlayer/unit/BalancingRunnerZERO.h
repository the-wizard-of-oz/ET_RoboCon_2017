#ifndef UNIT_BALANCING_RUNNER_ZERO_H
#define UNIT_BALANCING_RUNNER_ZERO_H

#include "MotorController.h"
#include "BalancingCalculator.h"
#include "GyroMonitor.h"
#include "BatteryMonitor.h"

#define STOP_ROTATE 0
#define ZEROYON 10
#define STOP 11
#define REDUCE 12

#define MIDDLE 10
#define SLOW 5
#define DEAD_SLOW 1
#define ZERO_SPEED 0

#define CONST_P 0.9
#define CONST_D -0.3


namespace unit
{
	class BalancingRunnerZERO
	{
	private:
		int mTurn;
		int mForward;
		int mPreviousPWMForward;
		MotorController* mMotorController;
		BalancingCalculator mBalancingCalculator;
		GyroMonitor* mGyroMonitor;
		BatteryMonitor mBatteryMonitor;

	public:
		BalancingRunnerZERO(MotorController* motorController, GyroMonitor* gyroMonitor);
		~BalancingRunnerZERO();
		void initializeDeviceAndLibrary();
		void move(int& direction, int forward);
		void stop();
	};
}  // namespace unit
#endif
