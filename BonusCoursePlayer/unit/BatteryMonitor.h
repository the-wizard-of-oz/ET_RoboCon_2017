#ifndef UNIT_BATTERY_MONITOR_H
#define UNIT_BATTERY_MONITOR_H

#include "Battery.h"

namespace unit
{
	class BatteryMonitor
	{
	private:
		Battery mBattery;

	public:
		BatteryMonitor();
		void getBatteryVoltageMv(int& val);
	};
}  // namespace unit
#endif
