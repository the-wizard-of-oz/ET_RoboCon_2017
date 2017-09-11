#ifndef UNIT_BALANCING_TRAVEL_H
#define UNIT_BALANCING_TRAVEL_H

#include "ITravel.h"
#include "GyroDriver.h"
#include "BatteryDriver.h"
#include "ITurn.h"
#include "IForward.h"
#include "BalancingController.h"

namespace unit
{
	class BalancingTravel
	: public ITravel
	{
	//
	protected:
		GyroDriver*    mGyroDriver;
		BatteryDriver* mBatteryDriver;
		ITurn*         mITurn;
		IForward*      mIForward;
		BalancingController* mBalancingController;
		
	public:
		BalancingTravel(MotorController* motorController, GyroDriver* gyroDriver, BatteryDriver* batteryDriver,
						ITurn* iTurn, IForward* iForward, BalancingController* balancingController);
		virtual ~BalancingTravel();

		virtual bool execute();
	};
}  // namespace unit
#endif
