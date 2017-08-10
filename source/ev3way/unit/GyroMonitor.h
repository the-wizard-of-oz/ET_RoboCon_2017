#ifndef UNIT_GYRO_MONITOR_H
#define UNIT_GYRO_MONITOR_H

#include "GyroSensor.h"
#include "ev3api.h"

namespace unit
{
	class GyroMonitor
	{
	private:
		int mGyroOffset;
		ev3api::GyroSensor* mGyroSensor;

	public:
		GyroMonitor();
		~GyroMonitor();
		void getAnglerVelocity(int& val);
		void getGyroOffset(int& val);
	};
}  // namespace unit
#endif
