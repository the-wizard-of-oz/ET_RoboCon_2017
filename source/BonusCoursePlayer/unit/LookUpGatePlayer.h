#ifndef LOOK_UP_GATE_PLAYER_H
#define LOOK_UP_GATE_PLAYER_H

#include "unit/BalancingRunnerZERO.h"
#include "unit/MotorController.h"
#include "unit/DistanceMeter.h"
#include "SonarMonitor.h"
#include "unit/TailMovement.h"

#define FIND_GATE 1
#define TAIL_STOP_MOVEMENT 2
#define TAIL_MOVE_AHEAD_1ST 3
#define TAIL_MOVE_AHEAD_2ND 4
#define TAIL_MOVE_BACK 5
#define RESET_BALANCE_RUNNING 6
#define LOOKUP_COMPLETE 7

#define GATE_PASS_DISTANCE 15//cm

#define LOOKUP_GATE_PASS_DISTANCE 350//mm
#define LOOKUP_GATE_BACK_DISTANCE 0//mm

namespace unit
{
	class LookUpGatePlayer{
	private:
		int mState;
		BalancingRunnerZERO* mBalancingRunnerZERO;
		DistanceMeter* mDistanceMeter;
		MotorController* mMotorController;
		TailMovement* mTailMovement;
		SonarMonitor* mSonarMonitor;

	public:
		LookUpGatePlayer(BalancingRunnerZERO* balancingRunnerZERO, DistanceMeter* distanceMeter, MotorController* motorController, TailMovement* tailMovement, SonarMonitor* sonarMonitor);
		~LookUpGatePlayer();

		bool execute();
	};


}


#endif
