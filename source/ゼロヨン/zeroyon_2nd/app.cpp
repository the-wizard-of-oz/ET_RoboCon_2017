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
#include "Run4mAndStop.h" 

using namespace ev3api;

// using宣言
using ev3api::GyroSensor;
using ev3api::TouchSensor;
using ev3api::Motor;

#define DEBUG

#ifdef DEBUG
#define _debug(x) (x)
#else
#define _debug(x)
#endif

/* Bluetooth */
static int32_t   bt_cmd = 0;      /* Bluetoothコマンド 1:リモートスタート */
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
GyroSensor  gGyroSensor(PORT_4);
TouchSensor gTouchSensor(PORT_1);
Motor       gLeftWheel(PORT_C);
Motor       gRightWheel(PORT_B);

//オブジェクトの定義
static Run4mAndStop *gRun4mAndStop;
static BeforeStart *gBeforeStart;
//static Start *Ev3Start;
//static Running *Ev3Running
static Stop *gStop;

static BalanceRunning *gBalanceRunning;


static void user_system_create()
{
	//タッチセンサ初期化待ち
	tslp_tsk(2);

	gRun4mAndStop = new Run4mAndStop(gBeforeStart,gStop);
	gBeforeStart = new BeforeStart(gTouchSensor);
//	Ev3Start = new Ev3Start();
//	Ev3Running = new Ev3Running();
	gStop = new Stop(gBalanceRunning);

	gBalanceRunning = new BalanceRunning(gGyroSensor);
}

static void user_system_destroy()
{
	delete gRun4mAndStop;
	delete gBeforeStart;
//	delete Ev3Start;
//	delete Ev3Running;
	delete gStop;

	delete gBalanceRunning;

}


/* メインタスク */
void main_task(intptr_t unused)
{
	user_system_create();

	//周期ハンドラ開始
	ev3_sta_cyc(EV3_CYC_ZEROYON);
		
		slp_tsk();  // バックボタンが押されるまで待つ

	// 周期ハンドラ停止
	ev3_stp_cyc(EV3_CYC_ZEROYON);

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

//*****************************************************************************
//zeroyonタスク
//
//概略:状態の切り替えを行う
//
//*****************************************************************************

void zeroyon_task(intptr_t exinf)
{
	if (ev3_button_is_pressed(BACK_BUTTON)) wup_tsk(MAIN_TASK);
	else gRun4mAndStop->runTask();

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
    while(1)
    {
        uint8_t c = fgetc(bt); /* 受信 */
        switch(c)
        {
        case '1':
            bt_cmd = 1;
            break;
        default:
            break;
        }
        fputc(c, bt); /* エコーバック */
    }
}
