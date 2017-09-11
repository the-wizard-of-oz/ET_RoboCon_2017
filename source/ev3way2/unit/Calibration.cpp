#include "Calibration.h"

namespace unit
{
	Calibration::Calibration()
	{
	}

	Calibration::~Calibration()
	{
		for(auto it = mCalibrators.begin(); it != mCalibrators.end(); ++it)
		{
			delete *it;
		}
		mCalibrators.clear();
		std::vector<ICalibrator*>().swap(mCalibrators);
	}

	bool Calibration::execute()
	{
		bool isSuccess = true;
		for(auto it = mCalibrators.begin(); it != mCalibrators.end(); ++it)
		{
			isSuccess &= (*it)->execute();
		}
		
		return isSuccess;
	}
	
	void Calibration::addCalibrator(ICalibrator* iCalibrator)
	{
		mCalibrators.push_back(iCalibrator);
	}
}  // namespace unit
