#ifndef UNIT_BRIGHTNESS_JUDGE_H
#define UNIT_BRIGHTNESS_JUDGE_H

#include "EndJudge.h"
#include "ColorSensorDriver.h"

namespace unit
{
	class BrightnessJudge
	: public EndJudge
	{
	//
	protected:
		int mThresholdLower;
		int mThresholdUpper;

	private:
		ColorSensorDriver* mColorSensorDriver;
		
	//
	public:
		BrightnessJudge();
		BrightnessJudge(ThresholdProcessingMode mode, int thresholdLower, int thresholdUpper, ColorSensorDriver* colorSensorDriver);
		virtual ~BrightnessJudge();

		virtual bool execute();
	};
}  // namespace unit
#endif
