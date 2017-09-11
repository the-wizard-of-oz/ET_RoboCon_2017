#include "TravelPreparationSequence.h"

namespace unit
{
	TravelPreparationSequence::TravelPreparationSequence(MotorController*     motorController,
														 BalancingController* balancingController)
	: ISequence(), mMotorController(motorController), mBalancingController(balancingController)
	{
	}
	
	TravelPreparationSequence::~TravelPreparationSequence()
	{
		mMotorController     = nullptr;
		mBalancingController = nullptr;
	}
	
	bool TravelPreparationSequence::execute()
	{
		mMotorController->initializeMotors();
		mBalancingController->Balance_Init();
		
		return true;
	}
}  // namespace unit
