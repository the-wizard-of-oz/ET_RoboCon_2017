#include "LookUpGatePlayer.h"
#include "UsingLCD.h"

namespace unit
{
	LookUpGatePlayer::LookUpGatePlayer(BalancingRunnerZERO* balancingRunnerZERO, DistanceMeter* distanceMeter, MotorController* motorController, TailMovement* tailMovement, SonarMonitor* sonarMonitor)
		:mBalancingRunnerZERO(balancingRunnerZERO)
		, mDistanceMeter(distanceMeter)
		, mMotorController(motorController)
		, mTailMovement(tailMovement)
		,mSonarMonitor(sonarMonitor)
	{
		mDistanceMeter->resetMeter();
	}
	LookUpGatePlayer::~LookUpGatePlayer()
	{
		delete mSonarMonitor;
	}

	bool LookUpGatePlayer::execute()
	{
		int distance = 0;
		int direction = 0;
		int right = 0;
		int left = 0;
		int runningDistance = 0;
		char str[100];

		switch (mState)
		{
		case FIND_GATE:
			sprintf(str, "look up:find               ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 2);
			mBalancingRunnerZERO->move(direction, MIDDLE);
			mSonarMonitor->getDistance(distance);
			if (distance < GATE_PASS_DISTANCE) mState = TAIL_STOP_MOVEMENT;
			break;

		case TAIL_STOP_MOVEMENT:
			sprintf(str, "look up:tail stop            ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 2);
			if (mTailMovement->shiftTailToStop())
			{
				mState = TAIL_MOVE_AHEAD_1ST;
				mMotorController->getEncoderCounts(right, left);
				mDistanceMeter->update(right, left);
				mDistanceMeter->resetMeter();
			}
			break;

		case TAIL_MOVE_AHEAD_1ST:
		case TAIL_MOVE_AHEAD_2ND:
			mTailMovement->TailRun(MIDDLE);
			mMotorController->getEncoderCounts(right, left);
			mDistanceMeter->update(right, left);
			runningDistance = (int)mDistanceMeter->getDistance();
			if (runningDistance > LOOKUP_GATE_PASS_DISTANCE && mState == TAIL_MOVE_AHEAD_1ST) mState = TAIL_MOVE_BACK;
			else if (runningDistance > LOOKUP_GATE_PASS_DISTANCE && mState == TAIL_MOVE_AHEAD_2ND) mState = RESET_BALANCE_RUNNING;
			sprintf(str, "look up:ahead  dis = %d     ", runningDistance);
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 2);
			break;

		case TAIL_MOVE_BACK:
			sprintf(str, "look up:back               ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 2);
			mTailMovement->TailRun(MIDDLE*-1);
			mMotorController->getEncoderCounts(right, left);
			mDistanceMeter->update(right, left);
			runningDistance = (int)mDistanceMeter->getDistance();
			if (runningDistance < LOOKUP_GATE_BACK_DISTANCE) mState = TAIL_MOVE_AHEAD_2ND;
			break;

		case RESET_BALANCE_RUNNING:
			sprintf(str, "look up:reset balance          ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 2);
			if(mTailMovement->returnToBalanceRun()) mState = LOOKUP_COMPLETE;
			break;
		case LOOKUP_COMPLETE:
			sprintf(str, "look up:complete               ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 2);
			break;

		default:
			mState = FIND_GATE;
			break;
		}

		if (mState == LOOKUP_COMPLETE) return 1;
		return 0;
	}
}
