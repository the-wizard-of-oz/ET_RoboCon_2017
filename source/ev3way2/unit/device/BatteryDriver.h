#ifndef UNIT_BATTERY_DRIVER_H
#define UNIT_BATTERY_DRIVER_H

#include "Battery.h"

namespace unit
{
	class BatteryDriver
	{
	private:
		Battery mBattery;

	public:
		int Ev3_Battery_Voltage_mV();
	};
}  // namespace unit
#endif
