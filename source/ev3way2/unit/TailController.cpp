#include "TailController.h"

namespace unit
{
	TailController::TailController()
	{
		isTailMotorInitialized = false;
		mTailMotorDriver = nullptr;
	}

	TailController::TailController(MotorDriver* tailMotorDriver)
	{
		isTailMotorInitialized = false;
		mTailMotorDriver = tailMotorDriver;
	}

	TailController::~TailController()
	{
		mTailMotorDriver = nullptr;
	}

	void clipPWM(int& pwm)
	{
		if(pwm < -100)
		{
			pwm = -100;
		}
		if(pwm >  100)
		{
			pwm =  100;
		}
	}

	bool TailController::execute(int targetAngle, tailControl::eCallMode callMode, tailControl::eControlSpeed controlSpeed, tailControl::eTerminateMode terminateMode)
	{
		bool isSuccess = false;

		if(!isTailMotorInitialized)
		{
			mTailMotorDriver->Reset();
			isTailMotorInitialized = true;
		}
		while(true)
		{
			int pwm = 0;
			int currentAngle = mTailMotorDriver->GetCount();

			if(isTailControlTerminate(currentAngle, targetAngle, terminateMode))
			{
				mTailMotorDriver->SetPWM(pwm);
				isSuccess = true;
				break;
			}
			else
			{
				int angleError = currentAngle - targetAngle;
				pwm = - getGain(controlSpeed) * angleError;
				clipPWM(pwm);
				mTailMotorDriver->SetPWM(pwm);
			}
			if(callMode == tailControl::eCycleCall)
			{
				break;
			}
		}

		return isSuccess;
	}

	bool TailController::isTailControlTerminate(int currentAngle, int targetAngle, tailControl::eTerminateMode terminateMode)
	{
		bool isTerminate = false;

		switch(terminateMode)
		{
			case tailControl::eLessThanTargetAngle:
				isTerminate = (currentAngle <  targetAngle);
				break;
			case tailControl::eEqualToTargetAngle:
				isTerminate = (currentAngle == targetAngle);
				break;
			case tailControl::eLargerThanTargetAngle:
				isTerminate = (currentAngle >  targetAngle);
				break;
			default:
				break;
		}

		return isTerminate;
	}

	float TailController::getGain(tailControl::eControlSpeed controlSpeed)
	{
		float gain = 0.f;

		switch(controlSpeed)
		{
			case tailControl::eLowSpeed:
				gain = 1.25;
				break;
			case tailControl::eMiddleSpeed:
				gain = 2.5;
				break;
			case tailControl::eHighSpeed:
				gain = 5.0;
				break;
			default:
				break;
		}

		return gain;
	}
}  // namespace unit
