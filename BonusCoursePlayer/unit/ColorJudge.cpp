#include "ColorJudge.h"
#include "../hardware_setting.h"
#include "Clock.h"

namespace unit
{
	ColorJudge::ColorJudge(TouchSensorMonitor* touchSensorMonitor)
	: mTouchSensorMonitor(touchSensorMonitor), mColorSensor(nullptr)
	{
		mColorSensor = new ev3api::ColorSensor(PORT_COLOR_SENSOR);
	}

	ColorJudge::~ColorJudge()
	{
		delete mColorSensor;
	}
	
	void ColorJudge::updateDeterminationValues()
	{
		// 黒、白、灰の順に更新
		{
			int value[3] = {0};
			ev3api::Clock clock;
			ev3_led_set_color(LED_OFF);
			for(int i = 0; i < 3; ++i)
			{
				mTouchSensorMonitor->waitUntilSensorOn();
				value[i] = mColorSensor->getBrightness();
				ev3_led_set_color(LED_RED);
				clock.sleep(2000);
				ev3_led_set_color(LED_OFF);
			}
			mDeterminationValueOfBlack = value[0];
			mDeterminationValueOfWhite = value[1];
			mDeterminationValueOfGray  = value[2];
		}
	}

	void ColorJudge::getDeterminationValues(int& black, int& white, int& gray)
	{
		black = mDeterminationValueOfBlack;
		white = mDeterminationValueOfWhite;
		gray  = mDeterminationValueOfGray;
	}

	colorType ColorJudge::judgeLineColor()
	{
		int val = mColorSensor->getBrightness();
		return (val < (mDeterminationValueOfGray + mDeterminationValueOfWhite) / 2) ? eBlack : eWhite;
	}
}  // namespace unit
