#ifndef UNIT_TAIL_ANGLE_CALIBRATOR_H
#define UNIT_TAIL_ANGLE_CALIBRATOR_H

#include "ICalibrator.h"
#include "TailAngle.h"
#include "TailController.h"
#include "GyroDriver.h"

namespace unit
{
	class TailAngleCalibrator
	: public ICalibrator
	{
		//
	private:
		TailAngle*      mTailAngle;
		TailController* mTailController;
		GyroDriver*     mGyroDriver;
		
		//
	public:
		TailAngleCalibrator(TouchSensorMonitor* touchSensorMonitor, LCD* lcd,
							TailAngle* tailAngle, TailController* tailController, GyroDriver* gyroDriver);
		virtual ~TailAngleCalibrator();

		virtual bool execute();
	};
}  // namespace unit
#endif
