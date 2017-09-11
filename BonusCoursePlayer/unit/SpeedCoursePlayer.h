#ifndef UNIT_SPEED_COURSE_PLAYER_H
#define UNIT_SPEED_COURSE_PLAYER_H

#include "PostureController.h"
#include "BalancingRunner.h"
#include "StartMonitor.h"
#include "SelfPositionChecker.h"

namespace unit
{
	class SpeedCoursePlayer
	{
	private:
		double mDistanceFromStartToGoalR;
		double mDistanceFronStartToGoalR;
		PostureController* mTailController;
		BalancingRunner* mBalancingRunner;
		StartMonitor mStartMonitor;
		SelfPositionChecker* mSelfPositionChecker;

	private:
		void intializeBalancingRunner();
		void playCourse();
		void calculateRunningDirection(int& direction);
		bool isSpeedCourseFinished();

	public:
		SpeedCoursePlayer(BalancingRunner* balancingRunner, PostureController* tailController, SelfPositionChecker* selfPositionChecker, StartMonitor startMonitor);
		~SpeedCoursePlayer();
		bool doPreparation();
		bool waitStartOrder();
		bool run();
	};
}  // namespace unit
#endif
