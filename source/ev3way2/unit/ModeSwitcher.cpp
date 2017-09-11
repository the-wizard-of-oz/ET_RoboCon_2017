#include "ModeSwitcher.h"

namespace unit
{
	ModeSwitcher::ModeSwitcher(Initialize* initialize, Calibration* calibration,
							   SpeedCoursePlayer* speedCoursePlayer, BonusCoursePlayer* bonusCoursePlayer)
	: mInitialize(initialize), mCalibration(calibration),
	  mSpeedCoursePlayer(speedCoursePlayer), mBonusCoursePlayer(bonusCoursePlayer)
	{
	}

	ModeSwitcher::~ModeSwitcher()
	{
		mInitialize  = nullptr;
		mCalibration = nullptr;
		mSpeedCoursePlayer = nullptr;
		mBonusCoursePlayer = nullptr;
	}

	void ModeSwitcher::execute()
	{
		switch(mMode)
		{
			case eModeInitialize:
				mInitialize->execute();
				mMode = eModeCalibration;
				break;
			case eModeCalibration:
				mCalibration->execute();
				mMode = eModeSpeedCourse;
				break;
			case eModeSpeedCourse:
				if(mSpeedCoursePlayer->execute())
				{
					mMode = eModeBonusCourse;
				}
				break;
			case eModeBonusCourse:
				mBonusCoursePlayer->execute();
				break;
		}
	}
}  // namespace unit
