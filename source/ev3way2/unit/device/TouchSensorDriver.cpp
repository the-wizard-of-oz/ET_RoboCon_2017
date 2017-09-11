#include "TouchSensorDriver.h"

namespace unit
{
	TouchSensorDriver::TouchSensorDriver()
	{
		mTouchSensor = nullptr;
	}

	TouchSensorDriver::TouchSensorDriver(const ePortS port)
	{
		mTouchSensor = new ev3api::TouchSensor(port);
	}

	TouchSensorDriver::~TouchSensorDriver()
	{
		if(mTouchSensor == nullptr) delete mTouchSensor;
	}

	bool TouchSensorDriver::IsPressed()
	{
		return mTouchSensor->isPressed();
	}
}  // namespace unit
