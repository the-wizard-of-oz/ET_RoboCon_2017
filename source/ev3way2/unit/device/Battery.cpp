#include "ev3api.h"
#include "Battery.h"

namespace unit
{
	int Battery::Ev3_Battery_Voltage_mV()
	{
		return ev3_battery_voltage_mV();
	}
}  // namespace ev3apiWrapper
