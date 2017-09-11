#include "TailMovement.h"
#include "../hardware_setting.h"
#include "UsingLCD.h"
#include <math.h>


namespace unit
{
	TailMovement::TailMovement(BalancingRunnerZERO* balancingRunnerZERO, MotorController* motorController)
		:mBalancingRunnerZERO(balancingRunnerZERO)
		,mMotorController(motorController)
		,mTailMotor(nullptr)
	{
		mTailMotor = new ev3api::Motor(PORT_TAIL_MOTOR);
		mStateChange = false;
		mState = TAIL_INITIALIZE;	
		mStateRun = WAIT_BEFORE_RUN;
		mWaitTimer = 0;
		mI = 0;
	}

	TailMovement::~TailMovement()
	{
		delete mTailMotor;
	}

	bool TailMovement::shiftTailToStop()
	{
		bool isComplete = false;
		int direction = NO_STAIRING;
		char str[100];

		switch (mState)
		{
		case TAIL_INITIALIZE:
			sprintf(str, "tail movement:initialize         ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 3);
			mTailMotor->reset();
			mBalancingRunnerZERO->move(direction, ZERO_SPEED);
			mState = TAIL_DOWN;
/*			if (mWaitTimer > SETTLED_TIME)
			{
				mState = TAIL_DOWN;
				mWaitTimer = 0;
			}
			mWaitTimer++;
*/			break;

		case TAIL_DOWN:
			sprintf(str, "tail movement:tail down          ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 3);
			mBalancingRunnerZERO->move(direction, ZERO_SPEED);
			if (isTailOnPosition((float)STOP_ANGLE, TAIL_SPEED_DIFF_MODE))
			{
				//mState = TAIL_STOP;
				mState = FRONT_A_WHILE;
			}
			break;

		case FRONT_A_WHILE:
			mMotorController->rotateMotors(MIDDLE, MIDDLE);
			if (mWaitTimer > BACK_TIME*2)
			{
				mWaitTimer = 0;
				mState = BACK_A_WHILE;
			}
			else mWaitTimer++;
			break;

		case BACK_A_WHILE:
			mMotorController->rotateMotors(HIGH_MIDDLE *-1, HIGH_MIDDLE *-1);
			if (mWaitTimer > BACK_TIME)
			{
				mWaitTimer = 0;
				mState = TAIL_STOP;
			}
			else mWaitTimer++;
			break;

		case TAIL_STOP:
			sprintf(str, "tail movement:tail stop          ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 3);
			mMotorController->rotateMotors(ZERO_SPEED, ZERO_SPEED);
			if (isTailOnPosition((float)STOP_ANGLE, TAIL_SPEED_DIFF_MODE))
			{
				mState = TAIL_WAIT_SET;
				mWaitTimer = 0;
			}
			break;

		case TAIL_WAIT_SET:
			isTailOnPosition((float)STOP_ANGLE, TAIL_SPEED_STOP);
			mWaitTimer++;
			if (mWaitTimer > WAIT_TIME)
			{
				mState = TAIL_SET_POSITION;
				mWaitTimer = 0;
			}
			break;

		case TAIL_SET_POSITION:
			sprintf(str, "tail movement:set position       ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 3);
			if (isTailOnPosition((float)SET_ANGLE, TAIL_SPEED_DIFF_MODE))
			{
				mState = MOVEMENT_COMPLETE;
			}
			break;

		case MOVEMENT_COMPLETE:
			sprintf(str, "tail movement:complete           ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 3);
			mMotorController->rotateMotors(ZERO_SPEED, ZERO_SPEED);
			mTailMotor->setPWM(0);
			isComplete = true;
			break;

		default:
			mState = TAIL_DOWN;
			break;
		}

		return isComplete;
	}

	bool TailMovement::shiftTail(int angle)
	{
		bool isComplete = false;
		char str[100];

		sprintf(str, "tail movement:shift tail          ");
		ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 3);
//		mMotorController->rotateMotors(ZERO_SPEED, ZERO_SPEED);
		if (isTailOnPosition((float)angle, TAIL_SPEED_SLOW)) isComplete = 1;

		return isComplete;
	}

	void TailMovement::TailRun(int speed)
	{
		char str[100];

		switch (mStateRun)
		{
		case WAIT_BEFORE_RUN:
			isTailOnPosition((float)SET_ANGLE, TAIL_SPEED_MIDDLE);
			if (mWaitTimer > SETTLED_TIME)mStateRun = TAIL_SET_MODE;
			else mWaitTimer++;
			break;

		case TAIL_SET_MODE:
			sprintf(str, "tail run:set           ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 3);
			if (isTailOnPosition((float)MOVE_ANGLE, TAIL_SPEED_MIDDLE)) mStateRun = TAIL_RUN_MODE;
			break;

		case TAIL_RUN_MODE:
			sprintf(str, "tail run:run           ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 3);
			mMotorController->rotateMotors(speed, speed);
			break;

		default :
			mStateRun = WAIT_BEFORE_RUN;
			break;
		}
		
	}
	void TailMovement::TailRunKeepPosture(int speed)
	{
		char str[100];
		
		switch (mStateRun)
		{
		case WAIT_BEFORE_RUN:
			isTailOnPosition((float)SET_ANGLE, TAIL_SPEED_DIFF_MODE);
			sprintf(str, "tail run:set           ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 3);
			if (mWaitTimer > SETTLED_TIME)mStateRun = TAIL_RUN_MODE;
			else mWaitTimer++;
			break;

		case TAIL_RUN_MODE:
			isTailOnPosition((float)SET_ANGLE, TAIL_SPEED_DIFF_MODE);
			sprintf(str, "tail run:run           ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 3);
			mMotorController->rotateMotors(speed, speed);
			break;

		default:
			mStateRun = WAIT_BEFORE_RUN;
			break;
		}

	}
	bool TailMovement::TailTurn360()
	{
		char str[100];

		switch (mStateTurn)
		{
		case WAIT_BEFORE_RUN:
			isTailOnPosition((float)SET_ANGLE, TAIL_SPEED_MIDDLE);
			if (mWaitTimer > SETTLED_TIME)mStateTurn = TAIL_SET_MODE;
			else mWaitTimer++;
			break;

		case TAIL_SET_MODE:
			sprintf(str, "tail turn:set           ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 3);
			if (isTailOnPosition((float)MOVE_ANGLE, TAIL_SPEED_MIDDLE))
			{
				mStateTurn = TAIL_RUN_MODE;
				mMotorController->getEncoderCounts(mTurnStartRight, mTurnStartLeft);
			}
			break;

		case TAIL_TURN_MODE:
			sprintf(str, "tail turn:run           ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 3);
			mMotorController->rotateMotors(SLOW, -1*SLOW);
			if (isTurn(STEP_TURN_360)) mStateTurn = TURN_COMPLETE;
			break;

		case TURN_COMPLETE:
			break;

		default:
			mStateTurn = WAIT_BEFORE_RUN;
			break;
		}
		if (mStateTurn == TURN_COMPLETE)
		{
			mStateTurn = WAIT_BEFORE_RUN;
			return 1;
		}
		return 0;

	}

	bool TailMovement::TailTurnLeft90()
	{
		char str[100];

		switch (mStateTurn)
		{
		case WAIT_BEFORE_RUN:
			isTailOnPosition((float)SET_ANGLE, TAIL_SPEED_MIDDLE);
			if (mWaitTimer > SETTLED_TIME)mStateTurn = TAIL_SET_MODE;
			else mWaitTimer++;
			break;

		case TAIL_SET_MODE:
			sprintf(str, "tail turn:set           ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 3);
			if (isTailOnPosition((float)MOVE_ANGLE, TAIL_SPEED_MIDDLE))
			{
				mStateTurn = TAIL_RUN_MODE;
				mMotorController->getEncoderCounts(mTurnStartRight, mTurnStartLeft);
			}
			break;

		case TAIL_TURN_MODE:
			sprintf(str, "tail turn:run           ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 3);
			mMotorController->rotateMotors(SLOW, -1 * SLOW);
			if (isTurn(STEP_TURN_90)) mStateTurn = TURN_COMPLETE;
			break;

		case TURN_COMPLETE:
			break;

		default:
			mStateTurn = WAIT_BEFORE_RUN;
			break;
		}
		if (mStateTurn == TURN_COMPLETE)
		{
			mStateTurn = WAIT_BEFORE_RUN;
			return 1;
		}
		return 0;

	}

	bool TailMovement::returnToBalanceRun()
	{
		int direction = 0;
		char str[100];

		switch (mStateReturn)
		{
		case STOP_POSITION:
			mMotorController->rotateMotors(ZERO_SPEED, ZERO_SPEED);
			sprintf(str, "return to balance:stop           ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 3);
			if (isTailOnPosition((float)STOP_ANGLE, TAIL_SPEED_DIFF_MODE))
			{
				mStateReturn = WAIT_POSITION_SETTLE;
			}
			break;
		case WAIT_POSITION_SETTLE:
			sprintf(str, "return to balance:start           ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 3);
			if (mWaitTimer > SETTLED_TIME)
			{
				mStateReturn = START_POSITION;
				mWaitTimer = 0;
				mBalancingRunnerZERO->initializeDeviceAndLibrary();
			}
			else
			{
				isTailOnPosition((float)STOP_ANGLE, TAIL_SPEED_DIFF_MODE);
				mWaitTimer++;
			}
			break;

		case START_POSITION:
			sprintf(str, "return to balance:start           ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 3);
			mBalancingRunnerZERO->move(direction, ZERO_SPEED);
			if (isTailOnPosition((float)RUN_ANGLE, TAIL_SPEED_SLOW))
			{
				mStateReturn = RETURN_COMPLETE;
			}
			break;

		case RETURN_COMPLETE:
			sprintf(str, "return to balance:complete           ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 3);
			mStateReturn = STOP_POSITION;
			return 1;
			break;

		default:
			mStateReturn = STOP_POSITION;
			break;
		}
		return 0;

	}

	bool TailMovement::isTailOnPosition(float targetDegree, int PWMSpeed)
	{
		char str[100];

		float diff = targetDegree - (float)mTailMotor->getCount();
		sprintf(str, "position: %d    ", (int)mTailMotor->getCount());
		ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 5);
		if (diff == 0)
		{
			mTailMotor->setPWM(0);
			mI = 0;
			return true;
		}
		else
		{
			if (PWMSpeed == TAIL_SPEED_DIFF_MODE) PWMSpeed = TAIL_SPEED_MIDDLE * (1 - 1 / diff) + mI/I_CONSTANT;
			if(diff<0)PWMSpeed = PWMSpeed * -1;
			mTailMotor->setPWM(PWMSpeed);
			mI += PWMSpeed;
			sprintf(str, "PWM Speed: %d", PWMSpeed);
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 4);
			return false;
		}

	}

	bool TailMovement::isTurn(int angle)
	{
		int right;
		int left;

		mMotorController->getEncoderCounts(right, left);
		if (right > mTurnStartRight + angle && left < mTurnStartLeft - angle) return 1;
		return 0;
	}
	void  TailMovement::stateReset()
	{
		mStateRun = WAIT_BEFORE_RUN;
		mStateTurn = WAIT_BEFORE_RUN;
		mI = 0;
	}
}
