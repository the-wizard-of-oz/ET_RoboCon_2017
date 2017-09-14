#ifndef UNIT_START_MONITOR_H
#define UNIT_START_MONITOR_H

#include "TouchSensorDriver.h"

namespace unit
{
	class StartMonitor
	{
	private:
		TouchSensorDriver* mTouchSensorDriver;
		bool mIsStartSignalReceived;
		bool mIsBluetoothStartSignalReceived;

	public:
		StartMonitor(TouchSensorDriver* touchSensorDriver);
		~StartMonitor();
		
		bool execute();
		bool isStartSignalReceived();
		bool isBluetoothStartSignalReceived();
		void updateBluetoothStartSignalStatus();
	};
}  // namespace unit
#endif
