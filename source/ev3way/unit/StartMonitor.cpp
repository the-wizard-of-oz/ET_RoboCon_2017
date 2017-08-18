#include "StartMonitor.h"

namespace unit
{
	StartMonitor::StartMonitor(TouchSensorMonitor* touchSensorMonitor)
	: mTouchSensorMonitor(touchSensorMonitor)
	{
	}

	StartMonitor::~StartMonitor()
	{
		mTouchSensorMonitor = nullptr;
	}
	
	bool StartMonitor::execute()
	{
		return mTouchSensorMonitor->waitUntilSensorOn();
	}
}  // namespace unit
