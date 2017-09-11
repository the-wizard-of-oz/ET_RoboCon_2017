#ifndef UNIT_COLOR_JUDGE_H
#define UNIT_COLOR_JUDGE_H

#include "ColorSensor.h"
#include "TouchSensorMonitor.h"

namespace unit
{
	enum colorType
	{
		eBlack = 0,
		eWhite = 1,
		eGlay = 2,
	};
		
	class ColorJudge
	{
	private:
		int mDeterminationValueOfBlack;
		int mDeterminationValueOfWhite;
		int mDeterminationValueOfGray;

		TouchSensorMonitor* mTouchSensorMonitor;
		ev3api::ColorSensor* mColorSensor;

	public:
		ColorJudge(TouchSensorMonitor* touchSensorMonitor);
		~ColorJudge();
		void updateDeterminationValues();
		void getDeterminationValues(int& black, int& white, int& gray);
		colorType judgeLineColor();
	};
}  // namespace unit
#endif
