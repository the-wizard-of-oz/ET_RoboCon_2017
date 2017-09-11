#ifndef UNIT_TRAVEL_PREPARATION_SEQUENCE_H
#define UNIT_TRAVEL_PREPARATION_SEQUENCE_H

#include "ISequence.h"
#include "MotorController.h"
#include "BalancingController.h"

namespace unit
{
	class TravelPreparationSequence
	: public ISequence
	{
		//
	private:
		MotorController*     mMotorController;
		BalancingController* mBalancingController;
		
		//
	public:
		TravelPreparationSequence(MotorController* motorController, BalancingController* balancingController);
		virtual ~TravelPreparationSequence();

		virtual bool execute();
	};
}  // namespace unit
#endif
