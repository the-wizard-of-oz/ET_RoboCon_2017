#ifndef FIND_STAIR_H
#define FIND_STAIR_H

#include "GyroMonitor.h"
#define DATA_NUMBER 20
#define GYRO_THRESHOLD_FIND 40
#define GYRO_THRESHOLD_OVER 100

namespace unit
{
	class FindStair{
	private:
		int meanGyroValue;
		int dataForCalculateMeanGyroValue[DATA_NUMBER];
		GyroMonitor *mGyroMonitor;
		void setGyroValue();
		bool checkGyroAndMotor(int threshold);
		void calculateMeanGyroValue();

	public:
		FindStair(GyroMonitor* gyroMonitor);
		~FindStair();
			
		bool isFinding();
		bool isOver();
	};

}


#endif