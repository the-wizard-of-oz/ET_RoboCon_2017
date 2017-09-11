#include "StartDashTravel.h"

namespace unit
{
	StartDashTravel::StartDashTravel(MotorController* motorController,
									 GyroDriver* gyroDriver,
									 BatteryDriver* batteryDriver,
									 ITurn* iTurn,
									 IForward* iForward,
									 BalancingController* balancingController,
									 TailAngle*      tailAngle,
									 TailController* tailController,
									 eTargetPosture  targetPosture,
									 tailControl::eControlSpeed  controlSpeed,
									 tailControl::eTerminateMode terminateMode)
	: BalancingTravel(motorController,
					  gyroDriver,
					  batteryDriver,
					  iTurn,
					  iForward,
					  balancingController),
	  mTailAngle(tailAngle),
	  mTailController(tailController),
	  mTargetPosture(targetPosture),
	  mControlSpeed(controlSpeed),
	  mTerminateMode(terminateMode)
	{
	}
	
	StartDashTravel::~StartDashTravel()
	{
		mTailController = nullptr;
	}
	
	bool StartDashTravel::execute()
	{
		bool isTravelCompleted = true;
		
		isTravelCompleted &= mTailController->execute(mTailAngle->GetAngle(mTargetPosture),
													  tailControl::eCycleCall,
													  mControlSpeed,
													  mTerminateMode);
		isTravelCompleted &= BalancingTravel::execute();
		
		return isTravelCompleted;
	}
}  // namespace unit
