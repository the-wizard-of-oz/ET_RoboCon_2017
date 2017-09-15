#include <math.h>
#include "Compass.h"
#include "../hardware_size.h"

namespace unit
{
	Compass::Compass()
	: IAnalogMeter()
	{
		mDirection = 0.f;
	}

	Compass::Compass(int rightEncoderCount, int leftEncoderCount)
	: IAnalogMeter(rightEncoderCount, leftEncoderCount)
	{
		mDirection = 0.f;
	}

	Compass::~Compass()
	{
	}

	void Compass::update(int rightEncoderCount, int leftEncoderCount)
	{
		int rightRotationMovement  = rightEncoderCount - mPreviousRightEncoderCount;
		int leftRotationMovement   = leftEncoderCount  - mPreviousLeftEncoderCount;
		mDirection += WHEEL_DIAMETER_MM * (rightRotationMovement - leftRotationMovement) / WHEEL_DISTANCE_MM;
		mPreviousRightEncoderCount = rightEncoderCount;
		mPreviousLeftEncoderCount  = leftEncoderCount;
	}

	float Compass::getDirection()
	{
		return mDirection;
	}
}  // namespace unit
