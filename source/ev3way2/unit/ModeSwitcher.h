#ifndef UNIT_MODE_SWITCHER_H
#define UNIT_MODE_SWITCHER_H

#include "Initialize.h"
#include "Calibration.h"
#include "SpeedCoursePlayer.h"
#include "BonusCoursePlayer.h"

namespace unit
{
	enum eMode
	{
		eModeInitialize,
		eModeCalibration,
		eModeSpeedCourse,
		eModeBonusCourse
	};

	class ModeSwitcher
	{
	private:
		eMode mMode;
		Initialize*  mInitialize;
		Calibration* mCalibration;
		SpeedCoursePlayer* mSpeedCoursePlayer;
		BonusCoursePlayer* mBonusCoursePlayer;

	public:
		ModeSwitcher(Initialize*  initialize,
					 Calibration* calibration,
					 SpeedCoursePlayer* speedCoursePlayer,
					 BonusCoursePlayer* bonusCoursePlayer);
		~ModeSwitcher();

		void execute();
	};
}  // namespace unit
#endif
