#ifndef UNIT_START_DASH_TRAVEL_H
#define UNIT_START_DASH_TRAVEL_H

#include "BalancingTravel.h"
#include "TailAngle.h"
#include "TailController.h"

namespace unit
{
	class StartDashTravel
	: public BalancingTravel
	{
	//
	public:
		TailAngle*      mTailAngle;
		TailController* mTailController;
		eTargetPosture  mTargetPosture;
		tailControl::eControlSpeed  mControlSpeed;
		tailControl::eTerminateMode mTerminateMode;
		
	//
	public:
		StartDashTravel(MotorController* motorController, GyroDriver* gyroDriver, BatteryDriver* batteryDriver,
						ITurn* iTurn, IForward* iForward, BalancingController* balancingController,
						TailAngle*      tailAngle,
						TailController* tailController,
						eTargetPosture  targetPosture,
						tailControl::eControlSpeed  controlSpeed,
						tailControl::eTerminateMode terminateMode);
		virtual ~StartDashTravel();

		virtual bool execute();
	};
}  // namespace unit
#endif
