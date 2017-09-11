#include "GyroDriver.h"

namespace unit
{
	const int GYRO_OFFSET = 0;

	GyroDriver::GyroDriver()
	{
		mGyroOffset = GYRO_OFFSET;
		mGyroSensor = nullptr;
	}

	GyroDriver::GyroDriver(const ePortS port)
	{
		mGyroOffset = GYRO_OFFSET;
		mGyroSensor = new ev3api::GyroSensor(port);
	}

	GyroDriver::~GyroDriver()
	{
		if(mGyroSensor != nullptr) delete mGyroSensor;
	}

	void GyroDriver::Reset()
	{
		mGyroSensor->reset();
	}

	int GyroDriver::GetAnglerVelocity()
	{
		return mGyroSensor->getAnglerVelocity();
	}

	int GyroDriver::GetAngle()
	{
		return mGyroSensor->getAngle();
	}

	int GyroDriver::getOffset()
	{
		return mGyroOffset;
	}
}  // namespace unit
