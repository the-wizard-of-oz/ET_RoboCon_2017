#include "TouchSensorMonitor.h"
#include "../hardware_setting.h"

namespace unit
{
	TouchSensorMonitor::TouchSensorMonitor()
	: mTouchSensor(nullptr)
	{
		mTouchSensor = new ev3api::TouchSensor(PORT_TOUCH_SENSOR);
	}
	
	TouchSensorMonitor::~TouchSensorMonitor()
	{
		delete mTouchSensor;
	}

	bool TouchSensorMonitor::waitUntilSensorOn()
	{
/*		while(!mTouchSensor->isPressed())
		{
			;
		}
		*/
		if (mTouchSensor->isPressed()) return true;
		else return false;
	}
}  // namespace unit
