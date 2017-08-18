//*************************************************
//Run4mAndStopíÜêg
//
//
//
//*************************************************

#include "ev3api.h"
#include "BalanceRunning.h"
//#include "GyroSensor.h"
#include "UsingLCD.h"

BalanceRunning::BalanceRunning(const ev3api::GyroSensor& gyrosensor)
	: mGyroSensor(gyrosensor)
{
	mGyroAngle = 0;
}

void BalanceRunning::executeRun(float straight, float turn)
{
	ev3_lcd_draw_string("in executeRun", 0, CALIB_FONT_HEIGHT * 1);
	mGyroAngle = mGyroSensor.getAnglerVelocity();
	return;
}