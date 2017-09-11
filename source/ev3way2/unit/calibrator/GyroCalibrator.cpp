#include "GyroCalibrator.h"
#include "ev3api.h"

namespace unit
{
	GyroCalibrator::GyroCalibrator(TouchSensorMonitor* touchSensorMonitor, LCD* lcd, GyroDriver* gyroDriver)
	: ICalibrator(touchSensorMonitor, lcd), mGyroDriver(gyroDriver)
	{
	}
	
	GyroCalibrator::~GyroCalibrator()
	{
		mGyroDriver = nullptr;
	}
	
	bool GyroCalibrator::execute()
	{
		waitForInput();
		mGyroDriver->Reset();
		ev3_led_set_color(LED_GREEN);
		tslp_tsk(1000);
		ev3_led_set_color(LED_OFF);

		return true;
	}
}  // namespace unit
