#include "Battery.h"
#include "ev3api.h"

namespace unit
{
	void Battery::getBatteryVoltageMv(int& val)
	{
		val = ev3_battery_voltage_mV();
	}
}  // namespace ev3apiWrapper
