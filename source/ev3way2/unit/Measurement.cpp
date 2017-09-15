#include <cstddef>
#include "Measurement.h"

namespace unit
{
	Measurement::Measurement(MotorController* motorController)
	: mIsEnable(false), mMotorController(motorController)
	{
	}

	Measurement::~Measurement()
	{
		mMotorController = nullptr;
		mAnalogMeters.clear();
		std::vector<IAnalogMeter*>().swap(mAnalogMeters);
	}

	void Measurement::execute()
	{
		int rightEncoderCount = 0;
		int leftEncoderCount  = 0;
		mMotorController->getEncoderCounts(rightEncoderCount, leftEncoderCount);
		for(auto it = mAnalogMeters.begin(); it != mAnalogMeters.end(); ++it)
		{
			if(!mIsEnable)
			{
				(*it)->initPrevEncoderCount(rightEncoderCount, leftEncoderCount);
				mIsEnable = true;
			}
			(*it)->update(rightEncoderCount, leftEncoderCount);
		}
	}

	void Measurement::addAnalogMeter(IAnalogMeter* iAnalogMeter)
	{
		mAnalogMeters.push_back(iAnalogMeter);
	}
}  // namespace unit
