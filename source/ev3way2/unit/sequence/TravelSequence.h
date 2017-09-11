#ifndef UNIT_TRAVEL_SEQUENCE_H
#define UNIT_TRAVEL_SEQUENCE_H

#include "ISequence.h"
#include "ITravel.h"
#include "Measurement.h"

namespace unit
{
	class TravelSequence
	: public ISequence
	{
		//
	private:
		EndMonitor*  mEndMonitor;
		ITravel*     mITravel;
		Measurement* mMeasurement;

		//
	public:
		TravelSequence(EndMonitor* endMonitor, ITravel* iTravel, Measurement* measurement);
		virtual ~TravelSequence();

		virtual bool execute();
	};
}  // namespace unit
#endif
