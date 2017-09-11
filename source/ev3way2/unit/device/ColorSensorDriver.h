#ifndef UNIT_COLOR_SENSOR_DRIVER_H
#define UNIT_COLOR_SENSOR_DRIVER_H

#include "ev3api.h"
#include "Port.h"
#include "ColorSensor.h"

namespace unit
{
	class ColorSensorDriver
	{
	private:
		ev3api::ColorSensor* mColorSensor;

	public:
		ColorSensorDriver();
		ColorSensorDriver(const ePortS port);
		~ColorSensorDriver();

		int GetBrightness();
	};
}  // namespace unit
#endif
