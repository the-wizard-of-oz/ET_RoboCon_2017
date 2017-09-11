#include "BalancingRunnerZERO.h"
#include "Clock.h"
#include "UsingLCD.h"

namespace unit
{
	const int TURN = 20;
	const int FORWARD = 20;

	BalancingRunnerZERO::BalancingRunnerZERO(MotorController* motorController, GyroMonitor* gyroMonitor)
	: mTurn(TURN), mForward(FORWARD), mMotorController(motorController), mGyroMonitor(gyroMonitor)
	{
		mPreviousPWMForward = 0;
	}

	BalancingRunnerZERO::~BalancingRunnerZERO()
	{
		mMotorController = nullptr;
		mGyroMonitor = nullptr;
	}
	
	void BalancingRunnerZERO::initializeDeviceAndLibrary()
	{
		int gyroOffset;
		mGyroMonitor->getGyroOffset(gyroOffset);
		mMotorController->initializeMotors();
		mBalancingCalculator.initializeBalancer();
	}

	void BalancingRunnerZERO::move(int& direction, int forward)
	{
		int fixedForward;

		fixedForward = forward * CONST_P + (forward - mPreviousPWMForward) * CONST_D;
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
			mBalancingCalculator.calculate((float)fixedForward,
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
		mPreviousPWMForward = (leftPWM + rightPWM) / 2;
		mMotorController->rotateMotors(rightPWM, leftPWM);
//		char str[100];
//		sprintf(str, "right = %d , left = %d", rightPWM, leftPWM);
//		ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 4);
//		ev3api::Clock clock;
//		clock.sleep(4);
	}
	void BalancingRunnerZERO::stop()
	{
		mMotorController->rotateMotors(STOP_ROTATE, STOP_ROTATE);
	}
}  // namespace unit
