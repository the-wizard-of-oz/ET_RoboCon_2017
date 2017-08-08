#include "GyroMonitor.h"
#include "../hardware_setting.h"

namespace unit
{
	const int GYRO_OFFSET = 0;
	bool needInitialize = true;

	GyroMonitor::GyroMonitor()
	: mGyroOffset(GYRO_OFFSET), mGyroSensor(nullptr)
	{
		mGyroSensor = new ev3api::GyroSensor(PORT_GYRO_SENSOR);
	}

	GyroMonitor::~GyroMonitor()
	{
		delete mGyroSensor;
	}
	
	void GyroMonitor::getAnglerVelocity(int& val)
	{
		if(needInitialize)
		{
			mGyroSensor->reset();
			needInitialize = false;
		}
		val = mGyroSensor->getAnglerVelocity();
	}

	void GyroMonitor::getGyroOffset(int& val)
	{
		val = GYRO_OFFSET;
	}
}  // namespace unit
