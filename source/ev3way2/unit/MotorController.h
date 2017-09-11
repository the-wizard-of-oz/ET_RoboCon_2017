#ifndef UNIT_MOTOR_CONTROLLER_H
#define UNIT_MOTOR_CONTROLLER_H

#include "ev3api.h"
#include "MotorDriver.h"

namespace unit
{
	class MotorController
	{
	private:
		MotorDriver* mRightMotorDriver;
		MotorDriver* mLeftMotorDriver;

	public:
		MotorController();
		MotorController(MotorDriver* rightMotorDriver, MotorDriver* leftMotorDriver);
		~MotorController();

		void initializeMotors();
		void rotateMotors(const int rightPWM, const int leftPWM);
		void getEncoderCounts(int& rightEncoderCount, int& leftEncoderCount);
	};
}  // namespace unit
#endif
