#include "BatteryMonitor.h"

namespace unit
{
	BatteryMonitor::BatteryMonitor()
	{
	}

	void BatteryMonitor::getBatteryVoltageMv(int& val)
	{
		mBattery.getBatteryVoltageMv(val);
	}
}  // namespace unit
