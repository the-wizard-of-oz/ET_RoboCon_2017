#ifndef UNIT_BALANCING_RUNNER_H
#define UNIT_BALANCING_RUNNER_H

#include "MotorController.h"
#include "BalancingCalculator.h"
#include "GyroMonitor.h"
#include "BatteryMonitor.h"

namespace unit
{
	class BalancingRunner
	{
	private:
		int mTurn;
		int mForward;
		MotorController* mMotorController;
		BalancingCalculator mBalancingCalculator;
		GyroMonitor* mGyroMonitor;
		BatteryMonitor mBatteryMonitor;

	public:
		BalancingRunner(MotorController* motorController, GyroMonitor* gyroMonitor);
		~BalancingRunner();
		void initializeDeviceAndLibrary();
		void move(int& direction);
	};
}  // namespace unit
#endif
