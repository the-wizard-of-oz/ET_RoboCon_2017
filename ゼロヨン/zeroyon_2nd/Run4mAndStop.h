//*********************************************
//Run4mAndStop用ヘッダー
//
//
//*********************************************
#ifndef RUN_4M_AND_STOP_H
#define RUN_4M_AND_STOP_H

#include "BeforeStart.h"

//#include "Start.h"
//#include "Running.h"

#include "Stop.h"

//タスク切り替え用
#define TASK_UNDEFINED 0
#define TASK_BEFORE_START 1
#define TASK_START 2
#define TASK_RUNNING 3
#define TASK_STOP 4

class Run4mAndStop
{
public:
	int	mState;
	Run4mAndStop(BeforeStart* beforestart, Stop* stop);
	void runTask();

private:
	Stop* mStop;
	BeforeStart* mBeforeStart;
};

#endif
