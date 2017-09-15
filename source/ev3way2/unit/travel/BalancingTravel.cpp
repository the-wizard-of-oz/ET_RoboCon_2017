#include "BalancingTravel.h"

namespace unit
{
	BalancingTravel::BalancingTravel(MotorController* motorController,
									 GyroDriver* gyroDriver,
									 BatteryDriver* batteryDriver,
									 ITurn* iTurn,
									 IForward* iForward,
									 BalancingController* balancingController)
	: ITravel(motorController), mGyroDriver(gyroDriver), mBatteryDriver(batteryDriver),
	  mITurn(iTurn), mIForward(iForward), mBalancingController(balancingController)
	{
	}
	
	BalancingTravel::~BalancingTravel()
	{
		mGyroDriver    = nullptr;
		mBatteryDriver = nullptr;
		delete mITurn;
		delete mIForward;
		mBalancingController = nullptr;
	}
	
	bool BalancingTravel::execute()
	{
		bool  needUpdate = true;
		float turn    = mITurn->getTurn(needUpdate);
		float forward = mIForward->getForward(needUpdate);
		float gyroAnglerVelocity = (float)mGyroDriver->GetAnglerVelocity();
		float gyroOffset         = (float)mGyroDriver->getOffset();
		float leftEncoderCount   = 0.f;
		float rightEncoderCount  = 0.f;
		{
			int rightEncoderCount_ = 0;
			int leftEncoderCount_  = 0;
			mMotorController->getEncoderCounts(rightEncoderCount_, leftEncoderCount_);
			rightEncoderCount = (float)rightEncoderCount_;
			leftEncoderCount  = (float)leftEncoderCount_;
		}
		float battery = mBatteryDriver->Ev3_Battery_Voltage_mV();
		signed char rightPWM = 0;
		signed char leftPWM  = 0;
		mBalancingController->Balance_Control(forward, turn, gyroAnglerVelocity, gyroOffset,
											  leftEncoderCount, rightEncoderCount, battery,
											  &rightPWM, &leftPWM);
		mMotorController->rotateMotors((int)rightPWM, (int)leftPWM);
		
		return true;
	}
}  // namespace unit
