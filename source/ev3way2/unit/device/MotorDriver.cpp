#include "MotorDriver.h"

namespace unit
{
	MotorDriver::MotorDriver()
	{
		mMotor = nullptr;
	}

	MotorDriver::MotorDriver(const ePortM port)
	{
		mMotor = new ev3api::Motor(port);
	}

	MotorDriver::~MotorDriver()
	{
		if(mMotor != nullptr) delete mMotor;
	}

	void MotorDriver::Reset()
	{
		mMotor->reset();
	}

	void MotorDriver::SetPWM(int pwm)
	{
		mMotor->setPWM(pwm);
	}

	int MotorDriver::GetCount()
	{
		return mMotor->getCount();
	}
}  // namespace unit
