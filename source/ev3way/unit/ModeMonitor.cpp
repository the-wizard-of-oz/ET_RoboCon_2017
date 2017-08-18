#include "ModeMonitor.h"

namespace unit
{
	ModeMonitor::ModeMonitor(Initializer initializer, SpeedCoursePlayer speedCoursePlayer, Calibrator calibrator, BonusCoursePlayer bonusCoursePlayer)
	: mInitializer(initializer), mSpeedCoursePlayer(speedCoursePlayer), mCalibrator(calibrator), mBonusCoursePlayer(bonusCoursePlayer)
	{
	}

	ModeMonitor::~ModeMonitor()
	{
	}
	
	void ModeMonitor::execute()
	{
		mInitializer.execute();
		mCalibrator.execute();
		// スピード競技攻略
		{
			mSpeedCoursePlayer.waitStartOrder();
			mSpeedCoursePlayer.doPreparation();
		}
	}
}  // namespace unit
