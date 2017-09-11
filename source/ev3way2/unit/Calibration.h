#ifndef UNIT_CALIBRATION_H
#define UNIT_CALIBRATION_H

#include <vector>
#include "ICalibrator.h"

namespace unit
{
	class Calibration
	{
	private:
		std::vector<ICalibrator*> mCalibrators;

	public:
		Calibration();
		~Calibration();

		bool execute();
		void addCalibrator(ICalibrator* iCalibrator);
	};
}  // namespace unit
#endif
