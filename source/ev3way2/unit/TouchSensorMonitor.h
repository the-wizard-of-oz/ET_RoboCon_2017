#ifndef UNIT_TOUCH_SENSOR_MONITOR_H
#define UNIT_TOUCH_SENSOR_MONITOR_H

#include "ev3api.h"
#include "TouchSensorDriver.h"

namespace unit
{
	class TouchSensorMonitor
	{
	private:
		TouchSensorDriver* mTouchSensorDriver;

	public:
		TouchSensorMonitor();
		TouchSensorMonitor(TouchSensorDriver* touchSensorDriver);
		~TouchSensorMonitor();

		bool waitUntilSensorOn();
	};
}  // namespace unit
#endif
