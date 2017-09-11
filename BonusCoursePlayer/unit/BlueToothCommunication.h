#ifndef BLUE_TOOTH_COMMUNICATION_H
#define BLUE_TOOTH_COMMUNICATION_H

#include "TouchSensorMonitor.h"
#include "GyroMonitor.h"
#include "ev3api.h"
#include "GyroSensor.h"
#include "TouchSensor.h"
#include "Motor.h"
#include "SonarSensor.h"


#define INITIALIZE_BT 0
#define SEND_PARAMETER 1

#define UPPER_LIMIT 11500

namespace unit
{
	class BlueToothCommunication{
	private:
		int mState;
		FILE *mBt;
		TouchSensorMonitor *mTouchSensorMonitor;
		GyroMonitor *mGyroMonitor;
		ev3api::GyroSensor* mGyroSensor;
		ev3api::TouchSensor* mTouchSensor;
		ev3api::Motor* mLeftMotor;
		ev3api::Motor* mRightMotor;
		ev3api::Motor* mTailMotor;
		ev3api::SonarSensor* mSonarSensor;

		int mTime;
		int mAngle;
		int mTouch;
		int mLMotor;
		int mRMotor;
		int mTMotor;
		int mSonar;
		
		void setAngle();
		void setTouch();
		void setLeftMotor();
		void setRightMotor();
		void setTailMotor();
		void setSonar();

	public:
		BlueToothCommunication(FILE *bt, TouchSensorMonitor *touchSensorMonitor, GyroMonitor *gyroMonitor);
		~BlueToothCommunication();

		bool execute();
	};

}


#endif