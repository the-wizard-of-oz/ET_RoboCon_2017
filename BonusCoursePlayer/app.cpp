/**
 ******************************************************************************
 ** ファイル名 : app.cpp
 **
 ** 概要 : 2017/8/5ゼロヨン攻略用
 **
 ** 注記 : 
 ******************************************************************************
 **/

#include "app.h"
#include "BonusCoursePlayer.h" 
#include "DebugStarter.h"
#include "unit/BalancingRunner.h"
#include "unit/StairPlayer.h"
#include "unit/GaragePlayer.h"
#include "unit/LookUpGatePlayer.h"
#include "unit/CalculateRunningDirection.h"
#include "GyroSensor.h"
#include "TouchSensor.h"
#include "ColorSensor.h"
#include "SonarSensor.h"
#include "Motor.h"

#include "BlueToothCommunication.h"

void *__dso_handle = 0;

// using宣言
using ev3api::GyroSensor;
using ev3api::TouchSensor;
using ev3api::ColorSensor;
using ev3api::SonarSensor;
using ev3api::Motor;

#define DEBUG

#ifdef DEBUG
#define _debug(x) (x)
#else
#define _debug(x)
#endif

/* Bluetooth */
//static int32_t   bt_cmd = 0;      /* Bluetoothコマンド 1:リモートスタート */
static FILE     *bt = NULL;      /* Bluetoothファイルハンドル */

/* 下記のマクロは個体/環境に合わせて変更する必要があります */
#define GYRO_OFFSET           0  /* ジャイロセンサオフセット値(角速度0[deg/sec]時) */
#define LIGHT_WHITE          40  /* 白色の光センサ値 */
#define LIGHT_BLACK           0  /* 黒色の光センサ値 */
#define SONAR_ALERT_DISTANCE 30  /* 超音波センサによる障害物検知距離[cm] */
#define TAIL_ANGLE_STAND_UP  93  /* 完全停止時の角度[度] */
#define TAIL_ANGLE_DRIVE      3  /* バランス走行時の角度[度] */
#define P_GAIN             2.5F  /* 完全停止用モータ制御比例係数 */
#define PWM_ABS_MAX          60  /* 完全停止用モータ制御PWM絶対最大値 */
//#define DEVICE_NAME     "ET0"  /* Bluetooth名 hrp2/target/ev3.h BLUETOOTH_LOCAL_NAMEで設定 */
//#define PASS_KEY        "1234" /* パスキー    hrp2/target/ev3.h BLUETOOTH_PIN_CODEで設定 */
#define CMD_START         '1'    /* リモートスタートコマンド */

/* LCDフォントサイズ */
#define CALIB_FONT (EV3_FONT_SMALL)
#define CALIB_FONT_WIDTH (6/*TODO: magic number*/)
#define CALIB_FONT_HEIGHT (8/*TODO: magic number*/)

// オブジェクトを静的に確保する
TouchSensor gTouchSensor(PORT_1);
SonarSensor gSonarSensor(PORT_2);
ColorSensor gColorSensor(PORT_3);
GyroSensor  gGyroSensor(PORT_4);

Motor		gTailMotor(PORT_A);
Motor       gRightMotor(PORT_B);
Motor       gLeftMotor(PORT_C);

//オブジェクトの定義
static unit::BalancingCalculator	*gBalancingCalculator;
static unit::BalancingRunner		*gBalancingRunner;
static unit::BalancingRunnerZERO	*gBalancingRunnerZERO;
static unit::BatteryMonitor			*gBatteryMonitor;
static BonusCoursePlayer			*gBonusCoursePlayer;
static unit::ColorJudge				*gColorJudge;
static unit::DebugStarter			*gDebugStarter;
static unit::PostureController		*gPostureController;
static unit::TouchSensorMonitor		*gTouchSensorMonitor;
static unit::FindStair *gFindStair;
static unit::IAnalogMeter *gIAnalogMeter;
static unit::DistanceMeter *gDistanceMeter;
static unit::TailMovement *gTailMovement;
static unit::MotorController		*gMotorController;
static unit::GyroMonitor			*gGyroMonitor;
static unit::GaragePlayer			*gGaragePlayer;
static unit::LookUpGatePlayer		*gLookUpGatePlayer;
static unit::CalculateRunningDirection		*gCalculateRunningDirection;
static unit::SelfPositionChecker	*gSelfPositionChecker;
static unit::SonarMonitor *gSonarMonitor;
static unit::StairPlayer			*gStairPlayer;
static unit::StartMonitor			*gStartMonitor;



static	unit::BlueToothCommunication *gBlueToothCommunication;

static void user_system_create()
{
	//タッチセンサ初期化待ち
	tslp_tsk(2);

	//デバッグ用COMポートモニタ
	gBlueToothCommunication = new unit::BlueToothCommunication(bt, gTouchSensorMonitor, gGyroMonitor);


	//他のインスタンスで呼ぶものは先に宣言する
	gBatteryMonitor			= new unit::BatteryMonitor();
	gBalancingCalculator	= new unit::BalancingCalculator();
	gMotorController		= new unit::MotorController();
	gGyroMonitor			= new unit::GyroMonitor();
	gSonarMonitor = new unit::SonarMonitor();
	gBalancingRunner = new unit::BalancingRunner(gMotorController, gGyroMonitor);
	gBalancingRunnerZERO = new unit::BalancingRunnerZERO(gMotorController, gGyroMonitor);
	gTouchSensorMonitor		= new unit::TouchSensorMonitor();
	gPostureController		= new unit::PostureController();
	gTailMovement = new unit::TailMovement(gBalancingRunnerZERO, gMotorController);
	
	gDistanceMeter = new unit::DistanceMeter(0,0);

	gFindStair = new unit::FindStair(gGyroMonitor);
	gColorJudge = new unit::ColorJudge(gTouchSensorMonitor);
	gSelfPositionChecker = new unit::SelfPositionChecker(gColorJudge);
	gCalculateRunningDirection = new unit::CalculateRunningDirection(gSelfPositionChecker);

	gStartMonitor = new unit::StartMonitor(gTouchSensorMonitor);
	gDebugStarter = new unit::DebugStarter(gPostureController, gStartMonitor, gBalancingRunner, gBalancingRunnerZERO, gDistanceMeter, gMotorController);
	gStairPlayer = new unit::StairPlayer(gBalancingRunnerZERO, gCalculateRunningDirection, gFindStair, gTailMovement, gDistanceMeter, gMotorController);
	gLookUpGatePlayer = new unit::LookUpGatePlayer(gBalancingRunnerZERO, gDistanceMeter, gMotorController,gTailMovement, gSonarMonitor);
	gGaragePlayer = new unit::GaragePlayer(gBalancingRunnerZERO, gCalculateRunningDirection, gDistanceMeter, gMotorController, gTailMovement);
	gBonusCoursePlayer = new BonusCoursePlayer(gDebugStarter, gStairPlayer, gLookUpGatePlayer, gGaragePlayer);

}

static void user_system_destroy()
{
	delete gIAnalogMeter;
	delete gDistanceMeter;
	delete gBatteryMonitor;
	delete gBalancingCalculator;
	delete gBalancingRunner;
	delete gFindStair;
	delete gGyroMonitor;
	delete gMotorController;
	delete gBonusCoursePlayer;
	delete gDebugStarter;
	delete gTouchSensorMonitor;
	delete gStartMonitor;
	delete gPostureController;
	delete gStairPlayer;
	delete gSonarMonitor;
	delete gLookUpGatePlayer;
	delete gGaragePlayer;
	delete gBalancingRunnerZERO;
	delete gTailMovement;

	delete gBlueToothCommunication;

}


/* メインタスク */
void main_task(intptr_t unused)
{
	user_system_create();

	//周期ハンドラ開始
	ev3_sta_cyc(EV3_CYC_ZEROYON);
	ev3_sta_cyc(EV3_CYC_COM);
		
		slp_tsk();  // バックボタンが押されるまで待つ

	// 周期ハンドラ停止
	ev3_stp_cyc(EV3_CYC_ZEROYON);
	ev3_stp_cyc(EV3_CYC_COM);

	user_system_destroy();

    ext_tsk();
}

//*****************************************************************************
//ev3_cyc_zeroyonタスク
//
//概略:zeroyonタスクを作成する
//
//*****************************************************************************

void ev3_cyc_zeroyon(intptr_t unused)
{
	act_tsk(ZEROYON_TASK);
}

void ev3_cyc_com(intptr_t unused)
{
	act_tsk(BT_TASK);
}


//*****************************************************************************
//zeroyonタスク
//
//概略:状態の切り替えを行う
//
//*****************************************************************************

void zeroyon_task(intptr_t exinf)
{

	if (ev3_button_is_pressed(BACK_BUTTON)) wup_tsk(MAIN_TASK);
	else gBonusCoursePlayer->runTask();

}

//*****************************************************************************
// 関数名 : bt_task
// 引数 : unused
// 返り値 : なし
// 概要 : Bluetooth通信によるリモートスタート。 Tera Termなどのターミナルソフトから、
//       ASCIIコードで1を送信すると、リモートスタートする。
//*****************************************************************************
void bt_task(intptr_t unused)
{
	gBlueToothCommunication->execute();
	

}
