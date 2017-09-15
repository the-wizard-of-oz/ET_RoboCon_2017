#include <math.h>
#include "Compass.h"
#include "../hardware_size.h"
#include "globalResourse.h"

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
		
		{
			char buf[64] = {0};
			sprintf(buf, "rDif:%4d(rEnc%4d), lDif%4d(lEnc%4d), dir:%4f\r\n",
					rightRotationMovement, rightEncoderCount,
					leftRotationMovement,  leftEncoderCount,  mDirection);
			gBluetoothLogger->log(buf, strlen(buf));
		}
	}

	float Compass::getDirection()
	{
		return mDirection;
	}
}  // namespace unit
