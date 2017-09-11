#ifndef GARAGE_PLAYER_H
#define GARAGE_PLAYER_H

#include "unit/BalancingRunnerZERO.h"
#include "unit/CalculateRunningDirection.h"
#include "unit/DistanceMeter.h"
#include "unit/MotorController.h"
#include "unit/TailMovement.h"

#define TO_GARAGE 1
#define SET_POSITION 2
#define CHANGE_POSTURE 3
#define GARAGE_STOP 4

#define GARAGE_DISTANCE 100
#define GARAGE_SET 10

#define REQUIRE_BALANCING 2 //TailMovementÇÃTAIL_DOWNÇ∆àÍèè 

namespace unit
{
	class GaragePlayer{
	private:
		BalancingRunnerZERO* mBalancingRunnerZERO;
		CalculateRunningDirection* mCalculateRunningDirection;
		DistanceMeter* mDistanceMeter;
		MotorController* mMotorController;
		TailMovement* mTailMovement;
		int mState;

	public:
		GaragePlayer(BalancingRunnerZERO* balancingRunnerZERO, CalculateRunningDirection* calculateRunningDirection, DistanceMeter* distanceMeter, MotorController* motorController, TailMovement* tailMovement);
		~GaragePlayer();

		bool execute();
	};


}


#endif
