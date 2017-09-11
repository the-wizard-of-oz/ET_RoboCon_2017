mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS += balancer.o balancer_param.o

APPL_CXXOBJS += \
	BalancingRunner.o \
	BalancingRunnerZERO.o \
	BalancingCalculator.o \
	BatteryMonitor.o \
	Battery.o \
	BlueToothCommunication.o \
	BonusCoursePlayer.o \
	CalculateRunningDirection.o \
	ColorJudge.o \
	DebugStarter.o \
	DistanceMeter.o \
	FindStair.o \
	GyroMonitor.o \
	GaragePlayer.o \
	IAnalogMeter.o \
	Initializer.o \
	LookUpGatePlayer.o \
	MotorController.o \
	PostureController.o \
	TailMovement.o \
	TouchSensorMonitor.o \
	SelfPositionChecker.o \
	SonarMonitor.o \
	StairPlayer.o \
	StartMonitor.o 




SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries

include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif

APPL_DIR += $(mkfile_path)app $(mkfile_path)unit

INCLUDES += \
	-I$(mkfile_path)app \
	-I$(mkfile_path)unit