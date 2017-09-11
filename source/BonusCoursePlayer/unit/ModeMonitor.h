#ifndef UNIT_MODE_MONITOR_H
#define UNIT_MODE_MONITOR_H

#include "Initializer.h"
#include "SpeedCoursePlayer.h"
#include "Calibrator.h"
#include "BonusCoursePlayer.h"

namespace unit
{
	class ModeMonitor
	{
	private:
		Initializer mInitializer;
		SpeedCoursePlayer mSpeedCoursePlayer;
		Calibrator mCalibrator;
		BonusCoursePlayer mBonusCoursePlayer;

	public:
		ModeMonitor(Initializer initializer, SpeedCoursePlayer speedCoursePlayer, Calibrator calibrator, BonusCoursePlayer bonusCoursePlayer);
		~ModeMonitor();
		void execute();
	};
}  // namespace unit
#endif
