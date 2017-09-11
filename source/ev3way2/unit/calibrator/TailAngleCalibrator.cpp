#include <cmath>
#include <stdlib.h>
#include "TailAngleCalibrator.h"
#include "ev3api.h"

namespace unit
{
	static const int CALIBRATION_RANGE = 20;
	static const int FALL_DETECT_ANGLE = 20;
	
	TailAngleCalibrator::TailAngleCalibrator(TouchSensorMonitor* touchSensorMonitor, LCD* lcd,
											 TailAngle*      tailAngle,
											 TailController* tailController,
											 GyroDriver*     gyroDriver)
	: ICalibrator(touchSensorMonitor, lcd),
	  mTailAngle(tailAngle),
	  mTailController(tailController),
	  mGyroDriver(gyroDriver)
	{
	}
	
	TailAngleCalibrator::~TailAngleCalibrator()
	{
		mTailAngle      = nullptr;
		mTailController = nullptr;
		mGyroDriver     = nullptr;
	}
	
	bool TailAngleCalibrator::execute()
	{
		bool isSuccess = false;
		
		waitForInput();
		mGyroDriver->Reset();
		int angleForResting = mTailAngle->GetAngle(ePostureForRestingInSpeedCourse);
		int startAngle = angleForResting - CALIBRATION_RANGE / 2;
		int endAngle   = angleForResting + CALIBRATION_RANGE / 2;
		for(int angle = startAngle; angle < endAngle; ++angle)
		{
			int gyroAngle = mGyroDriver->GetAngle();
			mTailController->execute(angle,
									 tailControl::eSingleCall,
									 tailControl::eLowSpeed,
									 tailControl::eEqualToTargetAngle);
			ev3_led_set_color(LED_RED);
			tslp_tsk(2000);
			ev3_led_set_color(LED_OFF);
			gyroAngle -= mGyroDriver->GetAngle();
			if(abs(gyroAngle) > FALL_DETECT_ANGLE)
			{
				isSuccess = true;
				tslp_tsk(2000);
				ev3_led_set_color(LED_GREEN);
				tslp_tsk(2000);
				ev3_led_set_color(LED_OFF);

				mTailAngle->SetAngle(ePostureForStartDash, angle + 2);
				mTailAngle->SetAngle(ePostureForRestingInSpeedCourse, angle - 1);
				mTailAngle->SetAngle(ePostureForRunningInSpeedCourse, angle - 60);
				char* buf = (char*)malloc(sizeof(char) * 64);
				sprintf(buf, "Dash:%d, Rst:%d, Run:%d",
						mTailAngle->GetAngle(ePostureForStartDash),
						mTailAngle->GetAngle(ePostureForRestingInSpeedCourse),
						mTailAngle->GetAngle(ePostureForRunningInSpeedCourse));
				notifyResult(buf);
				free(buf);
				mTailController->execute(mTailAngle->GetAngle(ePostureForRestingInSpeedCourse),
										 tailControl::eSingleCall,
										 tailControl::eLowSpeed,
										 tailControl::eEqualToTargetAngle);
				break;
			}
		}
		
		return isSuccess;
	}
}  // namespace unit
