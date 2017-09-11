#ifndef UNIT_DISTANCE_METER_H
#define UNIT_DISTANCE_METER_H

#include "IAnalogMeter.h"

namespace unit
{
	class DistanceMeter
		: public IAnalogMeter
	{
	private:
		float mDistance;

	public:
		DistanceMeter(int rightEncoderCount, int leftEncoderCount);
		virtual ~DistanceMeter();

		virtual void update(int rightEncoderCount, int leftEncoderCount);
		float getDistance();
		void resetMeter();
	};
}  // namespace unit
#endif
