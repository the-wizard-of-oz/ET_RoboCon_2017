#ifndef UNIT_MOTOR_DRIVER_H
#define UNIT_MOTOR_DRIVER_H

#include "ev3api.h"
#include "Port.h"
#include "Motor.h"

namespace unit
{
	class MotorDriver
	{
	private:
		ev3api::Motor* mMotor;

	public:
		MotorDriver();
		MotorDriver(const ePortM port);
		~MotorDriver();

		void Reset();
		void SetPWM(int pwm);
		int  GetCount();
	};
}  // namespace unit
#endif
