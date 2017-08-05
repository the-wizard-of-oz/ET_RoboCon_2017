//*********************************************
//Stop用ヘッダー
//
//
//*********************************************
#ifndef STOP_TASK_H
#define STOP_TASK_H

#include "BalanceRunning.h"

#define EV3_STOP 0

class Stop
{
public:
	Stop(BalanceRunning* balanceRunning);
	void executeStop();

private:
	BalanceRunning* mBalanceRunning;
	void waitThere();
};

#endif