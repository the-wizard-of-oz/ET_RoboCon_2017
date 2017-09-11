#include "MotorController.h"

namespace unit
{
	MotorController::MotorController()
	{
		mRightMotorDriver = nullptr;
		mLeftMotorDriver  = nullptr;
	}

	MotorController::MotorController(MotorDriver* rightMotorDriver, MotorDriver* leftMotorDriver)
	{
		mRightMotorDriver = rightMotorDriver;
		mLeftMotorDriver  = leftMotorDriver;
	}

	MotorController::~MotorController()
	{
		mRightMotorDriver = nullptr;
		mLeftMotorDriver  = nullptr;
	}

	void MotorController::initializeMotors()
	{
		mRightMotorDriver->Reset();
		mLeftMotorDriver->Reset();
	}

	void MotorController::rotateMotors(const int rightPWM, const int leftPWM)
	{
		mRightMotorDriver->SetPWM(rightPWM);
		mLeftMotorDriver->SetPWM(leftPWM);
	}

	void MotorController::getEncoderCounts(int& rightEncoderCount, int& leftEncoderCount)
	{
		rightEncoderCount = mRightMotorDriver->GetCount();
		leftEncoderCount  = mLeftMotorDriver->GetCount();
	}
}  // namespace unit
