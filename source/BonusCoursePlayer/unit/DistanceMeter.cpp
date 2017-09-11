#include <math.h>
#include "DistanceMeter.h"
#include "hardware_size.h"

namespace unit
{

	DistanceMeter::DistanceMeter(int rightEncoderCount, int leftEncoderCount)
	: IAnalogMeter(rightEncoderCount, leftEncoderCount)
	{
		mDistance = 0.f;
	}

	DistanceMeter::~DistanceMeter()
	{
	}

	void DistanceMeter::update(int rightEncoderCount, int leftEncoderCount)
	{
		int rightRotationMovement = rightEncoderCount - mPreviousRightEncoderCount;
		int leftRotationMovement  = leftEncoderCount  - mPreviousLeftEncoderCount;
		mDistance += (float)M_PI * WHEEL_DIAMETER_MM * (rightRotationMovement + leftRotationMovement) /2 / 360;
		mPreviousRightEncoderCount = rightEncoderCount;
		mPreviousLeftEncoderCount = leftEncoderCount;
	}

	float DistanceMeter::getDistance()
	{
		return mDistance;
	}

	void DistanceMeter::resetMeter()
	{
		mDistance = 0.f;

	}
}  // namespace unit
