#include "SpeedCoursePlayer.h"

namespace unit
{
	SpeedCoursePlayer::SpeedCoursePlayer(BalancingRunner* balancingRunner, PostureController* tailController, SelfPositionChecker* selfPositionChecker, StartMonitor startMonitor)
	: mTailController(tailController), mBalancingRunner(balancingRunner), mStartMonitor(startMonitor), mSelfPositionChecker(selfPositionChecker)
	{
	}

	SpeedCoursePlayer::~SpeedCoursePlayer()
	{
		mTailController      = nullptr;
		mBalancingRunner     = nullptr;
		mSelfPositionChecker = nullptr;
	}

	bool SpeedCoursePlayer::doPreparation()
	{
		intializeBalancingRunner();
		playCourse();
		return true;
	}

	void SpeedCoursePlayer::intializeBalancingRunner()
	{
		mBalancingRunner->initializeDeviceAndLibrary();
	}

	bool SpeedCoursePlayer::waitStartOrder()
	{
		return mStartMonitor.execute();
	}

	void SpeedCoursePlayer::playCourse()
	{
		bool isFinish = false;
		while(!isFinish)
		{
			if(!mTailController->isRunningPosture())
			{
				mTailController->shiftToRunningPosture();
			}
			run();
		}
	}

	bool SpeedCoursePlayer::run()
	{
		if(!(mSelfPositionChecker->reachedGoal()))
		{
			int direction;
			calculateRunningDirection(direction);
			mBalancingRunner->move(direction);
		}
		
		return true;
	}

	void SpeedCoursePlayer::calculateRunningDirection(int& direction)
	{
		// 左エッジ走行するよう設定
		if(mSelfPositionChecker->isOnBlackLine())
		{
			direction = -1;
		}
		else
		{
			direction = 1;
		}
	}

	bool SpeedCoursePlayer::isSpeedCourseFinished()
	{
		return false;
	}
}  // namespace unit
