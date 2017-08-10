//*************************************************
//BeforeStartíÜêg
//
//
//
//*************************************************

#include "BeforeStart.h"
#include "ev3api.h"
#include "UsingLCD.h"

BeforeStart::BeforeStart(const ev3api::TouchSensor& touchsensor)
	:mBeforeStartState(ONGOING),
	mTouchSensor(touchsensor)
{

}

void BeforeStart::executeBeforeStart()
{
	ev3_lcd_draw_string("BeforeStart task:exe", 0, CALIB_FONT_HEIGHT * 2);
	if (mTouchSensor.isPressed()) mBeforeStartState = DONE;
	return;
}

bool BeforeStart::isFinished()
{
	ev3_lcd_draw_string("BeforeStart task:isfinished", 0, CALIB_FONT_HEIGHT * 3);
	if (mBeforeStartState == DONE)	return DONE;
	else return ONGOING;

}