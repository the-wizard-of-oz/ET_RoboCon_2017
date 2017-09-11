#include "ITravel.h"

namespace unit
{
	ITravel::ITravel(MotorController* motorController)
	: mMotorController(motorController)
	{
	}
	
	ITravel::~ITravel()
	{
		mMotorController = nullptr;
	}
}  // namespace unit
