#include "TravelSequence.h"

namespace unit
{
	TravelSequence::TravelSequence(EndMonitor* endMonitor, ITravel* iTravel, Measurement* measurement)
	: mEndMonitor(endMonitor), mITravel(iTravel), mMeasurement(measurement)
	{
	}
	
	TravelSequence::~TravelSequence()
	{
		delete mEndMonitor;
		delete mITravel;
		mMeasurement = nullptr;
	}
	
	bool TravelSequence::execute()
	{
		bool isSuccess = true;

		isSuccess &= mITravel->execute();
		mMeasurement->execute();
		isSuccess &= mEndMonitor->execute();
		
		return isSuccess;
	}
}  // namespace unit
