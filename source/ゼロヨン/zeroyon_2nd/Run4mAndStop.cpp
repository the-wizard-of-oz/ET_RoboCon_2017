//*************************************************
//Run4mAndStop中身
//
//
//
//*************************************************

#include "ev3api.h"
#include "Run4mAndStop.h"
#include "UsingLCD.h"

//コンストラクタ
Run4mAndStop::Run4mAndStop(BeforeStart* beforestart, Stop* stop)
	: mBeforeStart(beforestart),
	  mStop(stop),
	  mState(TASK_UNDEFINED)
{
}

void Run4mAndStop::runTask()
{
	switch (mState)
	{
		case TASK_UNDEFINED:
			ev3_lcd_draw_string("switching task:undefined", 0, CALIB_FONT_HEIGHT * 1);
			mState = TASK_BEFORE_START;
			break;

		case TASK_BEFORE_START:
			ev3_lcd_draw_string("switching task:before start", 0, CALIB_FONT_HEIGHT * 1);
			mBeforeStart->executeBeforeStart();
			tempChecker = mBeforeStart->isFinished();
			if (tempChecker)	mState = TASK_STOP;	//本当はmState = TASK_START;
			break;
		/*			case TASK_START:
					runStart();
					break;
					case TASK_running:
					runRunning();
					break;
					*/	
		case TASK_STOP:
			ev3_lcd_draw_string("switching task:stop", 0, CALIB_FONT_HEIGHT * 1);
			mStop->executeStop();
			break;

		default:
			mState = TASK_UNDEFINED;
			break;
	}

}