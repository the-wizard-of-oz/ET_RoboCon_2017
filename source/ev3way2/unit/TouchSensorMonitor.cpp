#include "TouchSensorMonitor.h"

namespace unit
{
	TouchSensorMonitor::TouchSensorMonitor()
	{
		mTouchSensorDriver = nullptr;
	}

	TouchSensorMonitor::TouchSensorMonitor(TouchSensorDriver* touchSensorDriver)
	{
		mTouchSensorDriver = touchSensorDriver;
	}

	TouchSensorMonitor::~TouchSensorMonitor()
	{
		mTouchSensorDriver = nullptr;
	}

	bool TouchSensorMonitor::waitUntilSensorOn()
	{
		bool isSensorOn = false;

		while(!isSensorOn)
		{
			isSensorOn = mTouchSensorDriver->IsPressed();
		}
		
		return isSensorOn;
	}
}  // namespace unit
