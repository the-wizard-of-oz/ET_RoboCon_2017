#include "DebugStarter.h"
#include "UsingLCD.h"
#include "ev3api.h"

namespace unit
{
	DebugStarter::DebugStarter(PostureController* tailController, StartMonitor* startMonitor, BalancingRunner* balancingRunner, BalancingRunnerZERO* balancingRunnerZERO, DistanceMeter* distanceMeter, MotorController* motorController)
		: mTailController(tailController)
		, mStartMonitor(startMonitor)
		, mBalancingRunner(balancingRunner)
		, mBalancingRunnerZERO(balancingRunnerZERO)
		, mDistanceMeter(distanceMeter)
		, mMotorController(motorController)
	{
		mState = INITIALIZE;
	}
	
	DebugStarter::~DebugStarter()
	{
		mTailController = nullptr;
	}

	bool DebugStarter::execute()
	{
		int direction = 0;
		int right = 0;
		int left = 0;

		//char str[100];

		switch (mState)
		{
		case INITIALIZE:
			ev3_lcd_draw_string("switching start:init", 0, CALIB_FONT_HEIGHT * 3);
			mTailController->initializeMotor();
			mBalancingRunner->initializeDeviceAndLibrary();
			mState = WAIT;
			break;

		case WAIT:
			ev3_lcd_draw_string("switching start:wait", 0, CALIB_FONT_HEIGHT * 3);
			mTailController->shiftToRestingPosture();
			if(mStartMonitor->execute()) mState=GO;
			//if (mStartMonitor->execute()) mState = ZEROYON_START;//ƒ[ƒƒˆƒ“U—ª—p
			break;

		case ZEROYON_START:
			ev3_lcd_draw_string("zeroyon starter      ", 0, CALIB_FONT_HEIGHT * 3);
			if (mTailController->shiftToDashPosture()) mState = GO;
			break;

		case GO:
			ev3_lcd_draw_string("switching start:go", 0, CALIB_FONT_HEIGHT * 3);
			mBalancingRunner->move(direction);
			if (mTailController->shiftToRunningPosture()) mState=DONE;
			//if (mTailController->shiftToRunningPosture()) mState=ZEROYON; //ƒ[ƒƒˆƒ“U—ª—p
			break;

		case ZEROYON:
			ev3_lcd_draw_string("zeroyon mode ready      ", 0, CALIB_FONT_HEIGHT * 3);
			mBalancingRunnerZERO->move(direction, ZEROYON);
			mMotorController->getEncoderCounts(right, left);
			mDistanceMeter->update(right, left);
//			sprintf(str, "distance:%d", mDistanceMeter->getDistance());
//			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 5);
			if (mDistanceMeter->getDistance() > RUNNING_DISTANCE) mState = REDUCE;
			break;

		case REDUCE:
			ev3_lcd_draw_string("zeroyon mode reduce      ", 0, CALIB_FONT_HEIGHT * 3);
			mBalancingRunnerZERO->move(direction, REDUCE);
			mMotorController->getEncoderCounts(right, left);
			mDistanceMeter->update(right, left);
			//			sprintf(str, "distance:%d             ", (int)mDistanceMeter->getDistance());
			//			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 5);
			if (mDistanceMeter->getDistance() > REDUCE_DISTANCE) mState = STOP;
			break;

		case STOP:
			ev3_lcd_draw_string("zeroyon mode stop      ", 0, CALIB_FONT_HEIGHT * 3);
			mMotorController->getEncoderCounts(right, left);
			mDistanceMeter->update(right, left);
			//			sprintf(str, "distance:%d", mDistanceMeter->getDistance());
			//			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 5);
			mBalancingRunnerZERO->move(direction, STOP);
			break;

		default:
			ev3_lcd_draw_string("set initialize", 0, CALIB_FONT_HEIGHT * 3);
			mState = INITIALIZE;
			break;
		}

	if (mState == DONE) return 1;
	else return 0;
	}
}  // namespace unit
