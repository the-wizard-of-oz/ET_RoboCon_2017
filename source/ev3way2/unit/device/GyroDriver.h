#ifndef UNIT_GYRO_DRIVER_H
#define UNIT_GYRO_DRIVER_H

#include "ev3api.h"
#include "Port.h"
#include "GyroSensor.h"

namespace unit
{
	class GyroDriver
	{
	private:
		int mGyroOffset;
		ev3api::GyroSensor* mGyroSensor;

	public:
		GyroDriver();
		GyroDriver(const ePortS port);
		~GyroDriver();

		void Reset();
		int GetAnglerVelocity();
		int GetAngle();
		int getOffset();
	};
}  // namespace unit
#endif
