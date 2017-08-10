//*********************************************
//stop_task用ヘッダー
//
//
//*********************************************
#ifndef BEFORE_START_TASK_H
#define BEFORE_START_TASK_H

#include "TouchSensor.h"
#include "Motor.h"

#define ONGOING 0
#define DONE 1

class BeforeStart
{
public:
	BeforeStart(const ev3api::TouchSensor& touchsensor);
	void executeBeforeStart();
	bool isFinished();
private:
	const ev3api::TouchSensor& mTouchSensor;
	int mBeforeStartState;
};

#endif