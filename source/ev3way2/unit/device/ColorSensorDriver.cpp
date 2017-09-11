#include "ColorSensorDriver.h"

namespace unit
{
	ColorSensorDriver::ColorSensorDriver()
	{
		mColorSensor = nullptr;
	}

	ColorSensorDriver::ColorSensorDriver(const ePortS port)
	{
		mColorSensor = new ev3api::ColorSensor(port);
	}

	ColorSensorDriver::~ColorSensorDriver()
	{
		if(mColorSensor == nullptr) delete mColorSensor;
	}

	int ColorSensorDriver::GetBrightness()
	{
		return mColorSensor->getBrightness();
	}
}  // namespace unit
