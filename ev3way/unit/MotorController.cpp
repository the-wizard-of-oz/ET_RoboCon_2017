#include "MotorController.h"
#include "../hardware_setting.h"

namespace unit
{
	MotorController::MotorController()
	: mLeftMotor(nullptr), mRightMotor(nullptr)
	{
		mLeftMotor  = new ev3api::Motor(PORT_LEFT_MOTOR);
		mRightMotor = new ev3api::Motor(PORT_RIGHT_MOTOR);
	}

	MotorController::~MotorController()
	{
		delete mLeftMotor;
		delete mRightMotor;
	}

	void MotorController::initializeMotors()
	{
		mRightMotor->reset();
		mLeftMotor->reset();
	}

	void MotorController::rotateMotors(const int rightPWM, const int leftPWM)
	{
		mRightMotor->setPWM(rightPWM);
		mLeftMotor->setPWM(leftPWM);
	}

	void MotorController::getEncoderCounts(int& rightEncoderCount, int& leftEncoderCount)
	{
		rightEncoderCount = mRightMotor->getCount();
		leftEncoderCount  = mLeftMotor->getCount();
	}
}  // namespace unit
