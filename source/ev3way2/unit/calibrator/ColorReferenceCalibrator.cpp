#include "ColorReferenceCalibrator.h"
#include <algorithm>

namespace unit
{
	static const int NSAMPLE = 3;
	
	ColorReferenceCalibrator::ColorReferenceCalibrator(TouchSensorMonitor* touchSensorMonitor, LCD* lcd,
													   ColorSensorDriver* colorSensorDriver,
													   ColorReference*    colorReference)
	: ICalibrator(touchSensorMonitor, lcd),
	  mColorSensorDriver(colorSensorDriver),
	  mColorReference(colorReference)
	{
	}
	
	ColorReferenceCalibrator::~ColorReferenceCalibrator()
	{
		mColorSensorDriver = nullptr;
		mColorReference    = nullptr;
	}
	
	bool ColorReferenceCalibrator::execute()
	{
		int value[NSAMPLE] = {0};
		for(int i = 0; i < NSAMPLE; ++i)
		{
			waitForInput();
			value[i] = mColorSensorDriver->GetBrightness();
			ev3_led_set_color(LED_RED);
			tslp_tsk(1000);
			ev3_led_set_color(LED_OFF);
		}
		std::sort(value, value + NSAMPLE);
		mColorReference->mBlack = value[0];
		mColorReference->mGray  = value[1];
		mColorReference->mWhite = value[2];
		char* buf = (char *)malloc(sizeof(char) * 64);
		sprintf(buf, "Black: %d, Gray: %d, White: %d",
				mColorReference->mBlack, mColorReference->mGray, mColorReference->mWhite);
		notifyResult(buf);
		free(buf);
		ev3_led_set_color(LED_GREEN);
		tslp_tsk(1000);
		ev3_led_set_color(LED_OFF);
		
		return true;
	}
}  // namespace unit
