#ifndef EV3APIWRAPPER_BATTERY_H
#define EV3APIWRAPPER_BATTERY_H

namespace unit
{
	class Battery
	{
	public:
		void getBatteryVoltageMv(int& val);
	};
}  // namespace unit
#endif
