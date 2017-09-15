mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS += balancer.o balancer_param.o

APPL_CXXOBJS += BluetoothLogger.o \
				MotorDriver.o GyroDriver.o ColorSensorDriver.o TouchSensorDriver.o Battery.o BatteryDriver.o LCD.o \
				BalancingController.o TailController.o TouchSensorMonitor.o MotorController.o \
				IAnalogMeter.o DistanceMeter.o Compass.o Measurement.o \
				EndJudge.o NeverEndJudge.o BrightnessJudge.o DistanceJudge.o CompassJudge.o EndMonitor.o \
				TailAngle.o PostureController.o \
				ITurn.o BrightTraceTurn.o GrayTraceTurn.o PIDGrayTraceTurn.o \
				IForward.o SafelyTurnForward.o ConstantForward.o \
				ITravel.o BalancingTravel.o StartDashTravel.o \
				StartMonitor.o \
				ISequence.o StartMonitorSequence.o PostureControlSequence.o TravelPreparationSequence.o TravelSequence.o \
				ICalibrator.o TailAngleCalibrator.o GyroCalibrator.o ColorReferenceCalibrator.o \
				Initialize.o Calibration.o SpeedCoursePlayer.o BonusCoursePlayer.o \
				ModeSwitcher.o \
				EV3Way.o

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif

APPL_DIR += \
	$(mkfile_path)app \
	$(mkfile_path)unit \
	$(mkfile_path)unit/calibrator \
	$(mkfile_path)unit/device \
	$(mkfile_path)unit/forward \
	$(mkfile_path)unit/judge \
	$(mkfile_path)unit/meter \
	$(mkfile_path)unit/sequence \
	$(mkfile_path)unit/travel \
	$(mkfile_path)unit/turn

INCLUDES += \
	-I$(mkfile_path)app \
	-I$(mkfile_path)unit \
	-I$(mkfile_path)unit/calibrator \
	-I$(mkfile_path)unit/device \
	-I$(mkfile_path)unit/forward \
	-I$(mkfile_path)unit/judge \
	-I$(mkfile_path)unit/meter \
	-I$(mkfile_path)unit/sequence \
	-I$(mkfile_path)unit/travel \
	-I$(mkfile_path)unit/turn