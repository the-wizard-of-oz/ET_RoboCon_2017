#include "ICalibrator.h"

namespace unit
{
	ICalibrator::ICalibrator(TouchSensorMonitor* touchSensorMonitor, LCD* lcd)
	: mTouchSensorMonitor(touchSensorMonitor), mLCD(lcd)
	{
	}
	
	ICalibrator::~ICalibrator()
	{
		mTouchSensorMonitor = nullptr;
		mLCD = nullptr;
	}
	
	void ICalibrator::waitForInput()
	{
		mTouchSensorMonitor->waitUntilSensorOn();
	}
	
	void ICalibrator::notifyResult(char* str)
	{
		mLCD->display(str);
	}
}  // namespace unit
