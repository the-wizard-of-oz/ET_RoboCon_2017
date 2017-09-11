#include "PostureController.h"
#include "../hardware_setting.h"

namespace unit
{
	const int ANGLE_RESTING = 93;
	const int ANGLE_RUNNING =  3;
	const int ANGLE_DASH = 95;
	const int P_GAIN =  2.5F;   /* 完全停止用モータ制御比例係数 */
	const int PWM_ABS_MAX = 60; /* 完全停止用モータ制御PWM絶対最大値 */

	PostureController::PostureController()
		: mTailAngleResting(ANGLE_RESTING), mTailAngleRunning(ANGLE_RUNNING), mTailAngleDash(ANGLE_DASH), mTailMotor(nullptr)
	{
		mTailMotor = new ev3api::Motor(PORT_TAIL_MOTOR);
	}

	PostureController::~PostureController()
	{
		delete mTailMotor;
	}

	void PostureController::initializeMotor()
	{
		mTailMotor->reset();
	}

	bool PostureController::shiftPosture(float targetDegree)
	{
		bool isComplete = false;

		float diff = targetDegree - (float)mTailMotor->getCount();

		if (diff == 0)
		{
			mTailMotor->setPWM(0);
			isComplete = true;
		}
		else
		{
			float pwm = diff * P_GAIN; /* 比例制御 */
			/* PWM出力飽和処理 */
			if (pwm > PWM_ABS_MAX)
			{
				pwm = PWM_ABS_MAX;
			}
			else if (pwm < -PWM_ABS_MAX)
			{
				pwm = -PWM_ABS_MAX;
			}
			mTailMotor->setPWM(pwm);
		}
		
		return isComplete;
	}
	
	bool PostureController::shiftToRestingPosture()
	{
		return shiftPosture((float)mTailAngleResting);
	}

	bool PostureController::shiftToRunningPosture()
	{
		return shiftPosture((float)mTailAngleRunning);
	}
	bool PostureController::shiftToDashPosture()
	{
		return shiftPosture((float)mTailAngleDash);
	}
}  // namespace unit
