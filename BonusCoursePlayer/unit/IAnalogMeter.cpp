#include "IAnalogMeter.h"

namespace unit
{
/*	IAnalogMeter::IAnalogMeter()
	{
		mPreviousRightEncoderCount = 0;
		mPreviousLeftEncoderCount  = 0;
	}
*/
	IAnalogMeter::IAnalogMeter(int previousRightEncoderCount, int previousLeftEncoderCount)
	{
		mPreviousRightEncoderCount = previousRightEncoderCount;
		mPreviousLeftEncoderCount  = previousLeftEncoderCount;
	}

	IAnalogMeter::~IAnalogMeter()
	{
	}

	void IAnalogMeter::initPrevEncoderCount(int previousRightEncoderCount, int previousLeftEncoderCount)
	{
		mPreviousRightEncoderCount = previousRightEncoderCount;
		mPreviousLeftEncoderCount  = previousLeftEncoderCount;
	}
}  // namespace unit
