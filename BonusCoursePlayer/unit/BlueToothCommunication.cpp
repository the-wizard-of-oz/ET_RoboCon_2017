#include "BlueToothCommunication.h"
#include "../hardware_setting.h"
#include "UsingLCD.h"

namespace unit
{
	BlueToothCommunication::BlueToothCommunication(FILE *bt, TouchSensorMonitor *touchSensorMonitor, GyroMonitor *gyroMonitor)
		:mBt(bt)
		, mTouchSensorMonitor(touchSensorMonitor)
		, mGyroMonitor(gyroMonitor)
		, mGyroSensor(nullptr)
		, mTouchSensor(nullptr)
		, mLeftMotor(nullptr)
		, mRightMotor(nullptr)
		, mTailMotor(nullptr)
		, mSonarSensor(nullptr)
	{
		mGyroSensor = new ev3api::GyroSensor(PORT_GYRO_SENSOR);
		mTouchSensor = new ev3api::TouchSensor(PORT_TOUCH_SENSOR);
		mLeftMotor = new ev3api::Motor(PORT_LEFT_MOTOR);
		mRightMotor = new ev3api::Motor(PORT_RIGHT_MOTOR);
		mTailMotor = new ev3api::Motor(PORT_TAIL_MOTOR);
		mSonarSensor = new ev3api::SonarSensor(PORT_SONAR_SENSOR);

		mState = INITIALIZE_BT;
		mTime = 0;
		mAngle = 0;
		mTouch = 0;
		mLMotor = 0;
		mRMotor = 0;
		mTMotor = 0;
		mSonar = 0;
	}

	BlueToothCommunication::~BlueToothCommunication()
	{

	}

	bool BlueToothCommunication::execute()
	{
		char str[100];

		sprintf(str, "bt task enable");
		ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 7);
		
		switch (mState)
		{
			case INITIALIZE_BT:
				sprintf(str, "mode:initialze");
				ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 8);
				mBt = ev3_serial_open_file(EV3_SERIAL_BT);
				assert(mBt != NULL);
				
				if (mBt == NULL) sprintf(str, "mBt state = failed");
				else
				{
					sprintf(str, "mBt state = clear");
					mState = SEND_PARAMETER;
				}
				ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 9);

				fprintf(mBt, "time,gyro,touch,Lmotor,Rmotor,Tmotor,Sonar\n\r");
				
				break;

			case SEND_PARAMETER:
				sprintf(str, "mode:parameter send");
				ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 8);
				setAngle();
				setTouch();
				setLeftMotor();
				setRightMotor();
				setTailMotor();
				setSonar();
				fprintf(mBt, "%d, %d, %d, %d, %d, %d, %d\n\r", mTime, mAngle, mTouch, mLMotor, mRMotor,mTMotor, mSonar);
				break;

			default:
				sprintf(str, "mode:default");
				ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 8);
				mState = SEND_PARAMETER;
				break;

		}
		if (mTime >= UPPER_LIMIT) mTime = 0;
		mTime += 1;
		return 0;
	}

	void BlueToothCommunication::setAngle()
	{
		mAngle = mGyroSensor->getAnglerVelocity();
		return;
	}

	void BlueToothCommunication::setTouch()
	{
		mTouch = mTouchSensor->isPressed();
		return;
	}

	void BlueToothCommunication::setLeftMotor()
	{
		mLMotor = mLeftMotor->getCount();
		return;
	}

	void BlueToothCommunication::setRightMotor()
	{
		mRMotor = mRightMotor->getCount();
		return;
	}
	void BlueToothCommunication::setTailMotor()
	{
		mTMotor = mTailMotor->getCount();
		return;
	}
	void BlueToothCommunication::setSonar()
	{
		mSonar = mSonarSensor->getDistance();
		return;
	}



}
