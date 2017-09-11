#ifndef UNIT_MEASUREMENT_H
#define UNIT_MEASUREMENT_H

#include <vector>
#include "IAnalogMeter.h"
#include "MotorController.h"

namespace unit
{
	class Measurement
	{
	private:
		bool mIsEnable;
		std::vector<IAnalogMeter*> mAnalogMeters;
		MotorController* mMotorController;

	public:
		Measurement(MotorController* motorController);
		~Measurement();

		void execute();
		void addAnalogMeter(IAnalogMeter* iAnalogMeter);
	};
}  // namespace unit
#endif
