//*********************************************
//ヘッダー
//
//
//*********************************************
#ifndef BONUS_COURSE_PLAYER_H
#define BONUS_COURSE_PLAYER_H

#include "unit/DebugStarter.h"
#include "unit/StairPlayer.h"
#include "unit/GaragePlayer.h"
#include "unit/LookUpGatePlayer.h"
#include "unit/Initializer.h"


//タスク切り替え用
#define TASK_UNDEFINED		0
#define TASK_STAIR			1
#define TASK_LOOKUP_GATE	2
#define TASK_GARAGE			3
#define TASK_COMPLETE		4

#define DEBUG_TASK_START	10

class BonusCoursePlayer
{
public:
	BonusCoursePlayer(unit::DebugStarter* debugStarter, unit::StairPlayer* stairPlayer, unit::LookUpGatePlayer* lookUpGatePlayer, unit::GaragePlayer* garagePlayer);

	int ismState();

	void runTask();

private:
	int	mState;
	unit::DebugStarter* mDebugStarter;
	unit::StairPlayer* mStairPlayer;
	unit::LookUpGatePlayer* mLookUpGatePlayer;
	unit::GaragePlayer* mGaragePlayer;

};

#endif
