#ifndef UNIT_TOUCH_SENSOR_DRIVER_H
#define UNIT_TOUCH_SENSOR_DRIVER_H

#include "ev3api.h"
#include "Port.h"
#include "TouchSensor.h"

namespace unit
{
	class TouchSensorDriver
	{
	private:
		ev3api::TouchSensor* mTouchSensor;

	public:
		TouchSensorDriver();
		TouchSensorDriver(const ePortS port);
		~TouchSensorDriver();

		bool IsPressed();
	};
}  // namespace unit
#endif
