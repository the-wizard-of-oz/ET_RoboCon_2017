#ifndef UNIT_GYRO_CALIBRATOR_H
#define UNIT_GYRO_CALIBRATOR_H

#include "ICalibrator.h"
#include "GyroDriver.h"

namespace unit
{
	class GyroCalibrator
	: public ICalibrator
	{
		//
	private:
		GyroDriver* mGyroDriver;
		
		//
	public:
		GyroCalibrator(TouchSensorMonitor* touchSensorMonitor, LCD* lcd, GyroDriver* gyroDriver);
		virtual ~GyroCalibrator();

		virtual bool execute();
	};
}  // namespace unit
#endif
