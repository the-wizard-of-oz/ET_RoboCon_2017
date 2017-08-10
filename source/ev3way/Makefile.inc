mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS += balancer.o balancer_param.o

APPL_CXXOBJS += PostureController.o MotorController.o GyroMonitor.o BalancingRunner.o BalancingCalculator.o \
				BatteryMonitor.o Battery.o TouchSensorMonitor.o ColorJudge.o SelfPositionChecker.o \
				EV3Way.o ModeMonitor.o Initializer.o SpeedCoursePlayer.o StartMonitor.o \
				Calibrator.o LCD.o BonusCoursePlayer.o

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif

APPL_DIR += $(mkfile_path)app $(mkfile_path)unit

INCLUDES += \
	-I$(mkfile_path)app \
	-I$(mkfile_path)unit