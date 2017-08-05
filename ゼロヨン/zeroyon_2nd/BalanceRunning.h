//*********************************************
//BalanceRunning用ヘッダー
//
//
//*********************************************
#ifndef BALANCE_RUNNING_H
#define BALANCE_RUNNING_H

#include "GyroSensor.h"

class BalanceRunning
{
public:
	BalanceRunning(const ev3api::GyroSensor& gyrosensor);
	void executeRun(float straight,float turn);
private:
	const ev3api::GyroSensor& mGyroSensor;
	int16_t mGyroAngle;
};




#endif