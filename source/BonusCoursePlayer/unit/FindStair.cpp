#include "FindStair.h"
#include <stdlib.h>
#include "UsingLCD.h"


namespace unit
{
	FindStair::FindStair(GyroMonitor* gyroMonitor)
		:mGyroMonitor(gyroMonitor)
	{
		meanGyroValue=0;
		for (int clearCount = 0; clearCount < DATA_NUMBER; clearCount++)
			dataForCalculateMeanGyroValue[clearCount] = 0;
	}

	FindStair::~FindStair()
	{

	}

	bool FindStair::isFinding()
	{
		calculateMeanGyroValue();
		if (checkGyroAndMotor(GYRO_THRESHOLD_FIND)) return 1;
		return 0;
	}

	bool FindStair::isOver()
	{
		calculateMeanGyroValue();
		if (checkGyroAndMotor(GYRO_THRESHOLD_OVER)) return 1;
		return 0;
	}


	void FindStair::calculateMeanGyroValue()
	{
		int addValue = 0;
		char str[100];

		setGyroValue();
		for (int addCount = 0; addCount < DATA_NUMBER; addCount++)
			addValue += dataForCalculateMeanGyroValue[addCount];
		meanGyroValue = addValue / DATA_NUMBER;
		sprintf(str, "gyro mean value:%d            ", meanGyroValue);
		ev3_lcd_draw_string(str, 0, CALIB_FONT_HEIGHT * 5);
		return;
	}

	void FindStair::setGyroValue()
	{
		int angularVelocity = 0;
//		char str[100];

		for (int setCount = DATA_NUMBER - 1; setCount > 0; setCount--)
		{
			dataForCalculateMeanGyroValue[setCount] = dataForCalculateMeanGyroValue[setCount - 1];
		}

		mGyroMonitor->getAnglerVelocity(angularVelocity);
		dataForCalculateMeanGyroValue[0] = abs(angularVelocity);

		return;
	}

	bool FindStair::checkGyroAndMotor(int threshold)
	{
		if (meanGyroValue > threshold) return 1;
		return 0;
	}

}