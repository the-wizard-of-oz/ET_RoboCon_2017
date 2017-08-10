#include "BalancingRunner.h"
#include "Clock.h"

namespace unit
{
	const int TURN = 20;
	const int FORWARD = 20;

	BalancingRunner::BalancingRunner(MotorController* motorController, GyroMonitor* gyroMonitor)
	: mTurn(TURN), mForward(FORWARD), mMotorController(motorController), mGyroMonitor(gyroMonitor)
	{
	}

	BalancingRunner::~BalancingRunner()
	{
		mMotorController = nullptr;
		mGyroMonitor = nullptr;
	}
	
	void BalancingRunner::initializeDeviceAndLibrary()
	{
		int gyroOffset;
		mGyroMonitor->getGyroOffset(gyroOffset);
		mMotorController->initializeMotors();
		mBalancingCalculator.initializeBalancer();
	}

	void BalancingRunner::move(int& direction)
	{
		int mV, gyroOffset, anglerVelocity;
		{
			mBatteryMonitor.getBatteryVoltageMv(mV);
			mGyroMonitor->getGyroOffset(gyroOffset);
			mGyroMonitor->getAnglerVelocity(anglerVelocity);
		}
		int leftPWM, rightPWM;
		{
			int8_t leftPWM_, rightPWM_;
			int rightMotorAngle, leftMotorAngle;
			mMotorController->getEncoderCounts(rightMotorAngle, leftMotorAngle);
			mBalancingCalculator.calculate((float)FORWARD,
										   (float)direction * TURN,
										   (float)anglerVelocity,
										   (float)gyroOffset,
										   (float)rightMotorAngle,
										   (float)leftMotorAngle,
										   (float)mV,
										   (int8_t*)&leftPWM_,
										   (int8_t*)&rightPWM_);
			leftPWM  = leftPWM_;
			rightPWM = rightPWM_;
		}
		mMotorController->rotateMotors(rightPWM, leftPWM);
		ev3api::Clock clock;
		clock.sleep(4);
	}
}  // namespace unit
