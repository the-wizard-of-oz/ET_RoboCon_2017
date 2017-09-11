#ifndef UNIT_START_MONITOR_H
#define UNIT_START_MONITOR_H

#include "TouchSensorMonitor.h"

namespace unit
{
	class StartMonitor
	{
	private:
		TouchSensorMonitor* mTouchSensorMonitor;

	public:
		StartMonitor(TouchSensorMonitor* touchSensorMonitor);
		~StartMonitor();
		
		bool execute();
	};
}  // namespace unit
#endif
