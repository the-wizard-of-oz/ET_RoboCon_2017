#ifndef TAIL_MOVEMENT_H
#define TAIL_MOVEMENT_H

#include "ev3api.h"
#include "Motor.h"
#include "BalancingRunnerZERO.h"
#include "MotorController.h"

#define MOVEMENT_COMPLETE 1 
#define TAIL_DOWN 2
#define BACK_A_WHILE 7
#define FRONT_A_WHILE 8
#define TAIL_STOP 3
#define TAIL_WAIT_SET 6
#define TAIL_SET_POSITION 4
#define TAIL_INITIALIZE 5

#define RUN_BALANCE 1
#define RUN_SLOW 2
#define RUN_STOP 3

#define STOP_POSITION 1
#define WAIT_POSITION_SETTLE 4
#define START_POSITION 2
#define RETURN_COMPLETE 3

#define RUN_ANGLE 3
#define START_ANGLE 90
#define STOP_ANGLE 83
#define MOVE_ANGLE 65
#define SET_ANGLE 70
#define STAIR_OVER_ANGLE 75

#define TAIL_SPEED_DIFF_MODE 500
#define TAIL_SPEED_MIDDLE 10
#define TAIL_SPEED_SLOW 5
#define TAIL_SPEED_DEAD_SLOW 3
#define TAIL_SPEED_STOP 0

#define ZERO_SPEED 0
#define DEAD_SLOW 1
#define MIDDLE 10
#define HIGH_MIDDLE 30
#define FAST 50

#define NO_STAIRING 0

#define WAIT_BEFORE_RUN 3
#define TAIL_SET_MODE 1
#define TAIL_RUN_MODE 2
#define TAIL_TURN_MODE 5
#define TURN_COMPLETE 4

#define WAIT_TIME 100
#define SETTLED_TIME 500
#define BACK_TIME 25

#define STEP_TURN_360 360
#define STEP_TURN_90 90

#define I_CONSTANT 1000

namespace unit
{
	class TailMovement
	{
	private:
		int mState;
		int mStateReturn;
		bool mStateChange;
		int mStateRun;
		int mStateTurn;
		int mWaitTimer;
		int mTurnStartRight;
		int mTurnStartLeft;
		int mI;
		BalancingRunnerZERO* mBalancingRunnerZERO;
		MotorController* mMotorController;
		ev3api::Motor* mTailMotor;
		bool isTailOnPosition(float targetDegree, int PWMSpeed);
		bool isTurn(int angle);

	public:
		TailMovement(BalancingRunnerZERO* balancingRunnerZERO, MotorController* motorController);
		~TailMovement();

		bool shiftTailToStop();
		bool shiftTail(int angle);
		void TailRun(int speed);
		void TailRunKeepPosture(int speed);
		bool TailTurn360();
		bool TailTurnLeft90();
		bool returnToBalanceRun();
		void stateReset();
	};


}


#endif
