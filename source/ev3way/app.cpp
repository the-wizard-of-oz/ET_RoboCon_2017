/**
 ******************************************************************************
 ** ファイル名 : app.cpp
 **
 ** 概要 :
 **
 ** 注記 : 4msec間隔を取りながら繰り返し倒立振子走行、
 ******************************************************************************
 **/

#include "ev3api.h"
#include "app.h"

#include "unit/PostureController.h"
#include "unit/MotorController.h"
#include "unit/GyroMonitor.h"
#include "unit/BalancingRunner.h"
#include "unit/TouchSensorMonitor.h"
#include "unit/ColorJudge.h"
#include "unit/SelfPositionChecker.h"

#include "app/EV3Way.h"
#include "unit/ModeMonitor.h"
#include "unit/Initializer.h"
#include "unit/SpeedCoursePlayer.h"
#include "unit/StartMonitor.h"
#include "unit/Calibrator.h"
#include "unit/BonusCoursePlayer.h"

using namespace unit;

// Bluetooth（ログ出力用）
static FILE* bt = NULL; /* Bluetoothファイルハンドル */

/* メインタスク */
void main_task(intptr_t unused)
{
	// Bluetooth（ログ出力用）
	{
		/* Open Bluetooth file */
		bt = ev3_serial_open_file(EV3_SERIAL_BT);
		assert(bt != NULL);
	}
	
	// インスタンス生成
	PostureController tailController;
	MotorController motorController;
	GyroMonitor gyroMonitor;
	BalancingRunner balancingRunner(&motorController, &gyroMonitor);
	TouchSensorMonitor touchSensorMonitor;
	ColorJudge colorJudge(&touchSensorMonitor);
	SelfPositionChecker selfPositionChecker(&colorJudge);
	app::EV3Way ev3way(unit::ModeMonitor(unit::Initializer(&tailController),
										 unit::SpeedCoursePlayer(&balancingRunner, &tailController, &selfPositionChecker, unit::StartMonitor(&touchSensorMonitor)),
										 unit::Calibrator(&colorJudge),
										 unit::BonusCoursePlayer()));

	// 開始
	ev3way.execute();
	
	// インスタンス破棄（デストラクタに任せる）
}
