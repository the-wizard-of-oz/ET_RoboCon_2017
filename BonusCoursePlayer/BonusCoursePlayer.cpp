//*************************************************
//Run4mAndStop中身
//
//
//
//*************************************************

#include "ev3api.h"
#include "BonusCoursePlayer.h"
#include "UsingLCD.h"

//コンストラクタ
BonusCoursePlayer::BonusCoursePlayer(
	unit::DebugStarter* debugStarter, 
	unit::StairPlayer* stairPlayer, 
	unit::LookUpGatePlayer* lookUpGatePlayer, 
	unit::GaragePlayer* garagePlayer)
	:mDebugStarter(debugStarter), mStairPlayer(stairPlayer), mLookUpGatePlayer(lookUpGatePlayer), mGaragePlayer(garagePlayer)
{
}

void BonusCoursePlayer::runTask()
{
	char str[100];
	sprintf(str, "mState = %d", mState);
	ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 1);
	switch (mState)
	{
		case TASK_UNDEFINED:
			sprintf(str, "switching task:undefined");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 2);
			//mState = TASK_STAIR;
			mState = DEBUG_TASK_START;
			break;

		case TASK_STAIR:
			sprintf(str, "switching task:stair");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 2);
			if (mStairPlayer->execute()) mState = TASK_GARAGE;
			break;

		case TASK_LOOKUP_GATE:
			ev3_lcd_draw_string("                                ", 0, CALIB_FONT_HEIGHT * 1);
			ev3_lcd_draw_string("switching task:lookup gate", 0, CALIB_FONT_HEIGHT * 1);
			if (mLookUpGatePlayer->execute()) mState = TASK_GARAGE;
			break;

		case TASK_GARAGE:
			ev3_lcd_draw_string("                                ", 0, CALIB_FONT_HEIGHT * 1);
			ev3_lcd_draw_string("switching task:garage", 0, CALIB_FONT_HEIGHT * 1);
			if(mGaragePlayer->execute()) mState = TASK_COMPLETE;
			break;

		case DEBUG_TASK_START:
			sprintf(str, "switching task:debug start");
			ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 2);
			if(mDebugStarter->execute()) mState=TASK_STAIR;
//			if (mDebugStarter->execute()) mState = TASK_GARAGE;
//			if (mDebugStarter->execute()) mState = TASK_LOOKUP_GATE;
			break;

		case TASK_COMPLETE:
			break;

		default:
			ev3_lcd_draw_string("                                ", 0, CALIB_FONT_HEIGHT * 1);
			ev3_lcd_draw_string("switching task:default", 0, CALIB_FONT_HEIGHT * 1);
			mState = TASK_UNDEFINED;
			break;
	}

}


int BonusCoursePlayer::ismState()
{
	return mState;
}