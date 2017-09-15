#include "ev3api.h"
#include "app.h"

#include "BluetoothLogger.h"

#include "hardware_setting.h"
#include "MotorDriver.h"
#include "GyroDriver.h"
#include "ColorSensorDriver.h"
#include "TouchSensorDriver.h"
#include "BatteryDriver.h"
#include "LCD.h"

#include "BalancingController.h"
#include "TailController.h"
#include "TouchSensorMonitor.h"
#include "MotorController.h"

#include "DistanceMeter.h"
#include "Compass.h"
#include "Measurement.h"

#include "DistanceJudge.h"
#include "CompassJudge.h"
#include "EndJudge.h"
#include "NeverEndJudge.h"

#include "ColorReference.h"
#include "TailAngle.h"

#include "PostureController.h"

#include "StartMonitor.h"

#include "ModeSwitcher.h"
#include "Initialize.h"
#include "Calibration.h"
#include "SpeedCoursePlayer.h"
#include "BonusCoursePlayer.h"

#include "TailAngleCalibrator.h"
#include "GyroCalibrator.h"
#include "ColorReferenceCalibrator.h"

#include "GrayTraceTurn.h"
#include "PIDGrayTraceTurn.h"

#include "ConstantForward.h"
#include "SafelyTurnForward.h"

#include "StartDashTravel.h"
#include "BalancingTravel.h"

#include "StartMonitorSequence.h"
#include "PostureControlSequence.h"
#include "TravelPreparationSequence.h"
#include "TravelSequence.h"

#include "EV3Way.h"

//	------------------------------------------------------------
unit::BluetoothLogger* gBluetoothLogger = nullptr;

unit::MotorDriver* gTailMotorDriver  = nullptr;
unit::MotorDriver* gRightMotorDriver = nullptr;
unit::MotorDriver* gLeftMotorDriver  = nullptr;
unit::GyroDriver*  gGyroDriver       = nullptr;
unit::ColorSensorDriver* gColorSensorDriver = nullptr;
unit::TouchSensorDriver* gTouchSensorDriver = nullptr;
unit::BatteryDriver*     gBatteryDriver     = nullptr;
unit::LCD* gLCD = nullptr;

unit::BalancingController* gBalancingController = nullptr;
unit::TailController*      gTailController      = nullptr;
unit::TouchSensorMonitor*  gTouchSensorMonitor  = nullptr;
unit::MotorController*     gMotorController     = nullptr;

unit::DistanceMeter* gDistanceMeter = nullptr;
unit::Compass*       gCompass       = nullptr;
unit::Measurement*   gMeasurement   = nullptr;

unit::EndMonitor*    gEndMonitor    = nullptr;

unit::ColorReference gColorReference;
unit::TailAngle      gTailAngle;

unit::PostureController* gPostureController = nullptr;

unit::StartMonitor* gStartMonitor = nullptr;

unit::Initialize*  gInitialize  = nullptr;
unit::Calibration* gCalibration = nullptr;
unit::SpeedCoursePlayer* gSpeedCoursePlayer = nullptr;
unit::BonusCoursePlayer* gBonusCoursePlayer = nullptr;
unit::ModeSwitcher* gModeSwitcher = nullptr;

app::EV3Way* gEV3Way = nullptr;

//	------------------------------------------------------------
static void user_system_create()
{
	gBluetoothLogger   = new unit::BluetoothLogger();
	
	gTailMotorDriver   = new unit::MotorDriver(PORT_TAIL_MOTOR);
	gRightMotorDriver  = new unit::MotorDriver(PORT_RIGHT_MOTOR);
	gLeftMotorDriver   = new unit::MotorDriver(PORT_LEFT_MOTOR);
	gGyroDriver        = new unit::GyroDriver(PORT_GYRO_SENSOR);
	gColorSensorDriver = new unit::ColorSensorDriver(PORT_COLOR_SENSOR);
	gTouchSensorDriver = new unit::TouchSensorDriver(PORT_TOUCH_SENSOR);
	gBatteryDriver     = new unit::BatteryDriver();
	gLCD = new unit::LCD();

	gBalancingController = new unit::BalancingController();
	gTailController      = new unit::TailController(gTailMotorDriver);
	gTouchSensorMonitor  = new unit::TouchSensorMonitor(gTouchSensorDriver);
	gMotorController     = new unit::MotorController(gRightMotorDriver, gLeftMotorDriver);

	gDistanceMeter = new unit::DistanceMeter();
	gCompass       = new unit::Compass();
	gMeasurement   = new unit::Measurement(gMotorController);
	{
		gMeasurement->addAnalogMeter(gDistanceMeter);
		gMeasurement->addAnalogMeter(gCompass);
	}

	gPostureController = new unit::PostureController(gTailController, &gTailAngle);
	
	gStartMonitor = new unit::StartMonitor(gTouchSensorDriver);
	
	gInitialize   = new unit::Initialize(gPostureController);
	gCalibration  = new unit::Calibration();
	{
		gCalibration->addCalibrator(new unit::TailAngleCalibrator(gTouchSensorMonitor, gLCD, &gTailAngle, gTailController, gGyroDriver));
		gCalibration->addCalibrator(new unit::GyroCalibrator(gTouchSensorMonitor, gLCD, gGyroDriver));
		gCalibration->addCalibrator(new unit::ColorReferenceCalibrator(gTouchSensorMonitor, gLCD, gColorSensorDriver, &gColorReference));
	}
	gSpeedCoursePlayer = new unit::SpeedCoursePlayer();
	{
		gSpeedCoursePlayer->addSequence(new unit::StartMonitorSequence(gStartMonitor));
		gSpeedCoursePlayer->addSequence(new unit::PostureControlSequence(gPostureController, unit::ePostureForStartDash));
		gSpeedCoursePlayer->addSequence(new unit::TravelPreparationSequence(gMotorController, gBalancingController));
		// スタートダッシュ走行
		{
			unit::EndMonitor* endMonitor = new unit::EndMonitor();
			{
				endMonitor->addEndJudge(new unit::EndJudge());
			}
			unit::GrayTraceTurn* grayTraceTurn = new unit::GrayTraceTurn(gColorSensorDriver, &gColorReference);
			//unit::PIDGrayTraceTurn* pidGrayTraceTurn = new unit::PIDGrayTraceTurn(gColorSensorDriver, &gColorReference, 0.4f, 0.f, 0.f);
			unit::StartDashTravel*  startDashTravel  = new unit::StartDashTravel(gMotorController,
																				 gGyroDriver,
																				 gBatteryDriver,
																				 grayTraceTurn,
																				 //pidGrayTraceTurn,
																				 new unit::SafelyTurnForward(grayTraceTurn, 50.f),
																				 //new unit::ConstantForward(100.f),
																				 gBalancingController,
																				 &gTailAngle,
																				 gTailController,
																				 unit::ePostureForRunningInSpeedCourse,
																				 unit::tailControl::eHighSpeed,
																				 unit::tailControl::eLessThanTargetAngle);
			gSpeedCoursePlayer->addSequence(new unit::TravelSequence(endMonitor, startDashTravel, gMeasurement));
		}
		
		// ゴールまで走行
		{
			unit::EndMonitor* endMonitor = new unit::EndMonitor();
			{
				endMonitor->addEndJudge(new unit::DistanceJudge(unit::eBetweenLowerAndUpper, 10200.f, 10250.f, gDistanceMeter));
				endMonitor->addEndJudge(new unit::CompassJudge( unit::eBetweenLowerAndUpper, -30.f, 0.f, gCompass));
			}
			unit::GrayTraceTurn*   grayTraceTurn   = new unit::GrayTraceTurn(gColorSensorDriver, &gColorReference);
			unit::BalancingTravel* balancingTravel = new unit::BalancingTravel(gMotorController,
																			   gGyroDriver,
																			   gBatteryDriver,
																			   grayTraceTurn,
																			   new unit::SafelyTurnForward(grayTraceTurn, 50.f),
																			   gBalancingController);
			gSpeedCoursePlayer->addSequence(new unit::TravelSequence(endMonitor, balancingTravel, gMeasurement));
		}
	}
	gBonusCoursePlayer = new unit::BonusCoursePlayer();
	gModeSwitcher = new unit::ModeSwitcher(gInitialize, gCalibration, gSpeedCoursePlayer, gBonusCoursePlayer);

	gEV3Way = new app::EV3Way(gModeSwitcher);
}

static void user_system_destroy()
{
	delete gBluetoothLogger;
	
	delete gTailMotorDriver;
	delete gRightMotorDriver;
	delete gLeftMotorDriver;
	delete gGyroDriver;
	delete gColorSensorDriver;
	delete gTouchSensorDriver;
	delete gBatteryDriver;
	delete gLCD;

	delete gBalancingController;
	delete gTailController;
	delete gTouchSensorMonitor;
	delete gMotorController;

	delete gDistanceMeter;
	delete gCompass;
	delete gMeasurement;

	delete gPostureController;
	
	delete gStartMonitor;
	
	delete gInitialize;
	delete gCalibration;
	delete gSpeedCoursePlayer;
	delete gBonusCoursePlayer;
	delete gModeSwitcher;
	
	delete gEV3Way;
}

//	------------------------------------------------------------
void ev3_cyc_tracer(intptr_t exinf)
{
	act_tsk(TRACER_TASK);
}

//	------------------------------------------------------------
void tracer_task(intptr_t exinf)
{
	if (ev3_button_is_pressed(BACK_BUTTON))
	{
		wup_tsk(MAIN_TASK);
	}
	else
	{
		gEV3Way->execute();
	}
}

//	------------------------------------------------------------
void ev3_cyc_bluetooth_start(intptr_t exinf)
{
	act_tsk(BLUETOOTH_START_TASK);
}

//	------------------------------------------------------------
void bluetooth_start_task(intptr_t unused)
{
	if (ev3_button_is_pressed(BACK_BUTTON))
	{
		wup_tsk(MAIN_TASK);
	}
	else
	{
		if(!gStartMonitor->isStartSignalReceived())
		{
			if(!gStartMonitor->isBluetoothStartSignalReceived())
			{
				gStartMonitor->updateBluetoothStartSignalStatus();
			}
		}
	}
}

//	------------------------------------------------------------
void main_task(intptr_t unused)
{
	user_system_create();
	ev3_sta_cyc(EV3_CYC_TRACER);
	ev3_sta_cyc(EV3_CYC_BLUETOOTH_START);
	slp_tsk();
	ter_tsk(BLUETOOTH_START_TASK);
	ev3_stp_cyc(EV3_CYC_TRACER);
	ev3_stp_cyc(EV3_CYC_BLUETOOTH_START);
	user_system_destroy();
	ext_tsk();
}
