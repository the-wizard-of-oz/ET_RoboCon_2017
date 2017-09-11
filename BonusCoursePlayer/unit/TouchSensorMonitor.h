#ifndef UNIT_TOUCH_SENSOR_MONITOR_H
#define UNIT_TOUCH_SENSOR_MONITOR_H

#include "TouchSensor.h"
#include "ev3api.h"

namespace unit
{
	class TouchSensorMonitor
	{
	private:
		ev3api::TouchSensor* mTouchSensor;

	public:
		TouchSensorMonitor();
		~TouchSensorMonitor();
		bool waitUntilSensorOn();
	};
}  // namespace unit
#endif
