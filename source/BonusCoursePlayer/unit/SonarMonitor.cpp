#include "SonarMonitor.h"
#include "../hardware_setting.h"

namespace unit
{
	SonarMonitor::SonarMonitor()
	: mSonarSensor(nullptr)
	{
		mSonarSensor = new ev3api::SonarSensor(PORT_SONAR_SENSOR);
	}

	SonarMonitor::~SonarMonitor()
	{
		delete mSonarSensor;
	}
	
	void SonarMonitor::getDistance(int& val)
	{
		val = (int)mSonarSensor->getDistance();
	}

}  // namespace unit
