#include "GaragePlayer.h"
#include "UsingLCD.h"


namespace unit
{
	GaragePlayer::GaragePlayer(BalancingRunnerZERO* balancingRunnerZERO, CalculateRunningDirection* calculateRunningDirection, DistanceMeter* distanceMeter, MotorController* motorController, TailMovement* tailMovement)
		:mBalancingRunnerZERO(balancingRunnerZERO),
		mCalculateRunningDirection(calculateRunningDirection), 
		mDistanceMeter(distanceMeter), 
		mMotorController(motorController),
		mTailMovement(tailMovement)
	{
		mState = 0;
		mDistanceMeter->resetMeter();
			
	}

	GaragePlayer::~GaragePlayer()
	{

	}

	bool GaragePlayer::execute()
	{
		int direction = 0;
		int right = 0;
		int left = 0;
		char str[100];

		switch (mState)
		{
		case TO_GARAGE:
			sprintf(str, "garage player:to garage          ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 2);
			mBalancingRunnerZERO->move(direction, MIDDLE);
			mMotorController->getEncoderCounts(right, left);
			mDistanceMeter->update(right, left);
			if (mDistanceMeter->getDistance() > GARAGE_DISTANCE) mState = SET_POSITION;
			break;

		case SET_POSITION:
			sprintf(str, "garage player:set position       ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 2);
			mBalancingRunnerZERO->move(direction, DEAD_SLOW);
			mMotorController->getEncoderCounts(right, left);
			mDistanceMeter->update(right, left);
			if (mDistanceMeter->getDistance() > GARAGE_SET) mState = CHANGE_POSTURE;
			break;

		case CHANGE_POSTURE:
			sprintf(str, "garage player:change posture     ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 2);
			if (mTailMovement->shiftTailToStop())mState = GARAGE_STOP;
			break;

		case GARAGE_STOP:
			sprintf(str, "garage player:garage stop       ");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 2);

			mMotorController->rotateMotors(ZERO_SPEED, ZERO_SPEED);
			break;

		default:
			mState = TO_GARAGE;
			break;
		}
		return 0;
	}
}
