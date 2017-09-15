#ifndef UNIT_COMPASS_H
#define UNIT_COMPASS_H

#include "IAnalogMeter.h"

namespace unit
{
	class Compass
	: public IAnalogMeter
	{
	private:
		float mDirection;

	public:
		Compass();
		Compass(int rightEncoderCount, int leftEncoderCount);
		virtual ~Compass();

		virtual void update(int rightEncoderCount, int leftEncoderCount);
		float getDirection();
	};
}  // namespace unit
#endif
