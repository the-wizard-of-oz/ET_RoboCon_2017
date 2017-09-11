#include "StairPlayer.h"
#include "UsingLCD.h"

namespace unit
{
	StairPlayer::StairPlayer(BalancingRunnerZERO* balancingRunnerZERO, CalculateRunningDirection* calculateRunningDirection, FindStair* findStair, TailMovement* tailMovement, DistanceMeter* distanceMeter, MotorController* motorController)
		:mBalancingRunnerZERO(balancingRunnerZERO)
		, mCalculateRunningDirection(calculateRunningDirection)
		, mFindStair(findStair)
		, mTailMovement(tailMovement)
		, mDistanceMeter(distanceMeter)
		, mMotorController(motorController)

	{
		int right = 0;
		int left = 0;
		//mState = FIND_1ST_STAIR;
		mState = FOR_TEST;
		mDistanceMeter->resetMeter();
		mMotorController->getEncoderCounts(right, left);
		mDistanceMeter->update(right, left);
		mWaitTimer = 0;

	}
	StairPlayer::~StairPlayer()
	{

	}

	bool StairPlayer::execute()
	{
		int direction = 0;
		int right = 0;
		int left = 0;
//		int turnResult = 0;

		char str[100];

		switch (mState)
		{
		case FOR_TEST:
			mBalancingRunnerZERO->move(direction, SLOW);
			mMotorController->getEncoderCounts(right, left);
			mDistanceMeter->update(right, left);
			if (mDistanceMeter->getDistance() > TEST_DISTANCE) mState = PREPARE_FIND_STAIR;
			sprintf(str, "stair player:test         ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 2);
			break;

		case PREPARE_FIND_STAIR:
			sprintf(str, "stair player:prepare         ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 2);
			if (mTailMovement->shiftTailToStop()) mState = WAIT_BEFORE_AHEAD;
			break;

		case WAIT_BEFORE_AHEAD:
			sprintf(str, "stair player:wait         ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 2);
			mWaitTimer++;
			if (mWaitTimer > GYRO_SETTLING_TIME)
			{
				mState = FIND_1ST_STAIR;
				mWaitTimer = 0;
				mDistanceMeter->resetMeter();
				mDistanceMeter->update(right, left);
			}
			break;

		case FIND_1ST_STAIR:
			sprintf(str, "stair player:find 1         ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 2);
			mTailMovement->TailRunKeepPosture(SLOW);
			mMotorController->getEncoderCounts(right, left);
			mDistanceMeter->update(right, left);
			if (mFindStair->isFinding() || mDistanceMeter->getDistance() > STAIR_DISTANCE)
			{
				mState = UP_1ST_STAIR;
				mStateOverStair = FIND_STAIR;
				mTailMovement->stateReset();
			}
			break;

		case UP_1ST_STAIR:
			sprintf(str, "stair player:up 1         ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 2);

			switch (mStateOverStair)
			{
			case FIND_STAIR:
				sprintf(str, "up stair:find         ");
				ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 3);
				mTailMovement->TailRunKeepPosture(STOP);
				mDistanceMeter->resetMeter();
				mMotorController->getEncoderCounts(right, left);
				mDistanceMeter->update(right, left);
				mStateOverStair = LEAVE_A_BIT;
				mTailMovement->stateReset();
				break;

			case LEAVE_A_BIT:
				sprintf(str, "up stair:leave         ");
				ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 3);
				mTailMovement->TailRunKeepPosture(-1 * SLOW);
				mMotorController->getEncoderCounts(right, left);
				mDistanceMeter->update(right, left);
				if (mDistanceMeter->getDistance() < LEAVE_DISTANCE)
				{
					mStateOverStair = ACCLERATION;
					mTailMovement->stateReset();
				}
				break;

			case ACCLERATION:
				sprintf(str, "up stair:accel         ");
				ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 3);
				mTailMovement->TailRunKeepPosture(HIGH_MIDDLE);
				mMotorController->getEncoderCounts(right, left);
				mDistanceMeter->update(right, left);
				mTailMovement->shiftTail(SET_ANGLE);
				if (mDistanceMeter->getDistance() > CENTER_DISTANCE)
				{
					mStateOverStair = UP_COMPLETE;
					//mTailMovement->stateReset();
				}
				break;

			case UP_COMPLETE:
				sprintf(str, "up stair:comp         ");
				ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 3);
				mTailMovement->TailRunKeepPosture(ZERO_SPEED);
				mTailMovement->stateReset();
				mTailMovement->shiftTail(SET_ANGLE);
				mState = TURN_1ST;
				break;

			default:
				mStateOverStair = FIND_STAIR;
				break;

			}
			break;

		case TURN_1ST:
			sprintf(str, "stair player:turn 1         ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 2);
			mTailMovement->shiftTail(SET_ANGLE);
			break;

		default:
			mState = PREPARE_FIND_STAIR;
			break;
		}

/*		switch (mState)
		{

		case FIND_1ST_STAIR:
			direction = 0; //テスト用
			//			direction = mCalculateRunningDirection->calculate();
			mBalancingRunnerZERO->move(direction, MIDDLE);
			sprintf(str, "stair player:find 1 mSt=%d St=%d    ",mState, mFindStair->isFinding());
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 2);
			if (mFindStair->isFinding() == SET)
			{
				mStateOverStair = FIND_STAIR;
				mState = UP_1ST_STAIR;
			}
			break;

		case FIND_2ND_STAIR:

			direction = 0; //テスト用
			//			direction = mCalculateRunningDirection->calculate();
			mTailMovement->TailRun(SLOW);
			sprintf(str, "stair player:find 2 mSt=%d St=%d    ", mState, mFindStair->isFinding());
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 2);
			if (mFindStair->isFinding() == SET)
			{
				mStateOverStair = FIND_STAIR;
				mState = UP_2ND_STAIR;
			}
			break;

		case UP_1ST_STAIR:
		case UP_2ND_STAIR:
			sprintf(str, "stair player:up               ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 2);
			switch (mStateOverStair)
			{
			case FIND_STAIR:
				mDistanceMeter->resetMeter();
				mDistanceMeter->update(right, left);
				mStateOverStair = LEAVE_A_BIT;
				break;

			case LEAVE_A_BIT:
				if (mState == UP_1ST_STAIR) mBalancingRunnerZERO->move(direction, -1 * SLOW);
				if (mState == UP_2ND_STAIR) mTailMovement->TailRun(-1 * SLOW);
				mMotorController->getEncoderCounts(right, left);
				mDistanceMeter->update(right, left);
				if (mDistanceMeter->getDistance() < LEAVE_DISTANCE) mStateOverStair = CHANGE_POSTURE;
				break;

			case STOP_BY_TAIL:
				if (mTailMovement->shiftTailToStop())  mStateOverStair = CHANGE_POSTURE;
				break;

			case CHANGE_POSTURE:
				if (mTailMovement->shiftTail(STAIR_OVER_ANGLE))  mStateOverStair = OVER_STAIR;
				break;

			case OVER_STAIR:
				mTailMovement->TailRun(FAST);
				if (mFindStair->isOver())
				{
					mStateOverStair = SET_ON_CENTER;
					mDistanceMeter->resetMeter();
					mDistanceMeter->update(right, left);
				}
				break;

			case SET_ON_CENTER:
				mTailMovement->TailRun(SLOW);
				mMotorController->getEncoderCounts(right, left);
				mDistanceMeter->update(right, left);
				if (mDistanceMeter->getDistance() > CENTER_DISTANCE) mStateOverStair = CHANGE_POSTURE;
				break;

			case OVER_STAIR_COMPLETE:
				mDistanceMeter->resetMeter();
				mDistanceMeter->update(right, left);
				break;

			default:
				mStateOverStair = FIND_STAIR;
				break;
			}

			if (mStateOverStair == OVER_STAIR_COMPLETE)
			{
				mStateOverStair = FIND_STAIR;
				if (mState == UP_1ST_STAIR) mState = BALANCING_TURN_1ST;
				if (mState == UP_2ND_STAIR) mState = BALANCING_TURN_2ND;
			}
			break;

		case BALANCING_TURN_1ST:
		case BALANCING_TURN_2ND:
			sprintf(str, "stair player:turn               ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 2);
			turnResult = mTailMovement->TailTurn360();
			if (turnResult && mState == BALANCING_TURN_1ST) mState = FIND_2ND_STAIR;
			if (turnResult && mState == BALANCING_TURN_2ND) mState = TURN_LEFT;
			break;

		case TURN_LEFT:
			sprintf(str, "stair player:turn left               ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 2);
			if (mTailMovement->TailTurnLeft90()) mState = DOWN_STAIR;
			break;

		case DOWN_STAIR:
			sprintf(str, "stair player:down               ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 2);
			mTailMovement->TailRun(MIDDLE);
			if (mFindStair->isOver()) mState = STAIR_COMPLETE;
			break;

		case STAIR_COMPLETE:
			sprintf(str, "stair player:comp               ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 3);
			break;

		default:
			sprintf(str, "stair player:default               ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 3);
			mState = FIND_1ST_STAIR;
			break;

		}*/
		if (mState == STAIR_COMPLETE)return 1;
		return 0;
	}
}
