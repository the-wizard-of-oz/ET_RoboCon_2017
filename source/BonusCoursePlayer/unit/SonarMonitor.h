#ifndef UNIT_SONAR_MONITOR_H
#define UNIT_SONAR_MONITOR_H

#include "SonarSensor.h"
#include "ev3api.h"

namespace unit
{
	class SonarMonitor
	{
	private:
		ev3api::SonarSensor* mSonarSensor;

	public:
		SonarMonitor();
		~SonarMonitor();
		void getDistance(int& val);
	};
}  // namespace unit
#endif
