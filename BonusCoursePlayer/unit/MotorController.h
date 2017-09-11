#ifndef UNIT_MOTOR_CONTROLLER_H
#define UNIT_MOTOR_CONTROLLER_H

#include "ev3api.h"
#include "Motor.h"

namespace unit
{
	class MotorController
	{
	private:
		ev3api::Motor* mLeftMotor;
		ev3api::Motor* mRightMotor;

	public:
		MotorController();
		~MotorController();
		void initializeMotors();
		void rotateMotors(const int rightPWM, const int leftPWM);
		void getEncoderCounts(int& rightEncoderCount, int& leftEncoderCount);
	};
}  // namespace unit
#endif
