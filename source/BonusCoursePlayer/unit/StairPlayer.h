#ifndef STAIR_PLAYER_H
#define STAIR_PLAYER_H

#include "unit/BalancingRunnerZERO.h"
#include "unit/CalculateRunningDirection.h"
#include "unit/FindStair.h"
#include "TailMovement.h"
#include "DistanceMeter.h"
#include "MotorController.h"

#define FIND_1ST_STAIR		0
#define UP_1ST_STAIR		1
#define TURN_1ST			2
#define FIND_2ND_STAIR		3
#define UP_2ND_STAIR		4
#define BALANCING_TURN_2ND	5
#define TURN_LEFT			8
#define DOWN_STAIR			6
#define STAIR_COMPLETE		7
#define PREPARE_FIND_STAIR 9
#define WAIT_BEFORE_AHEAD 10

#define FOR_TEST 100

#define FIND_STAIR 1
#define LEAVE_A_BIT 2
#define STOP_BY_TAIL 7
#define CHANGE_POSTURE 3
#define OVER_STAIR 4
#define SET_ON_CENTER 6
#define OVER_STAIR_COMPLETE 5
#define ACCLERATION 8
#define UP_COMPLETE 9

#define SET 1

#define LEAVE_DISTANCE -30
#define CENTER_DISTANCE 200
#define TEST_DISTANCE 50
#define STAIR_DISTANCE 300

#define GYRO_SETTLING_TIME 500

namespace unit
{
	class StairPlayer
	{
	private:
		BalancingRunnerZERO* mBalancingRunnerZERO;
		CalculateRunningDirection* mCalculateRunningDirection;
		FindStair* mFindStair;
		TailMovement* mTailMovement;
		DistanceMeter* mDistanceMeter;
		MotorController* mMotorController;
		int mState;
		int mStateOverStair;
		int mWaitTimer;
		bool stairJudge();
		bool balancingTurn();
		bool upStair();
		bool downStair();
		bool returnToLine();


	public:
		StairPlayer(BalancingRunnerZERO* balancingRunnerZERO, CalculateRunningDirection* calculateRunningDirection, FindStair* findStair, TailMovement* tailMovement, DistanceMeter* distanceMeter, MotorController* motorController);
		~StairPlayer();

		bool execute();
	};


}


#endif
