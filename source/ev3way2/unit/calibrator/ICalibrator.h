#ifndef UNIT_I_CALIBRATOR_H
#define UNIT_I_CALIBRATOR_H

#include "TouchSensorMonitor.h"
#include "LCD.h"

namespace unit
{
	class ICalibrator
	{
		//
	protected:
		TouchSensorMonitor* mTouchSensorMonitor;
		LCD* mLCD;
		
		//
	public:
		ICalibrator(TouchSensorMonitor* touchSensorMonitor, LCD* lcd);
		virtual ~ICalibrator();

		virtual bool execute() = 0;
		
	protected:
		void waitForInput();
		void notifyResult(char* str);
	};
}  // namespace unit
#endif
