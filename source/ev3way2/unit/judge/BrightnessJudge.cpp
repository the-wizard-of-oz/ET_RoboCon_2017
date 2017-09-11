#include "BrightnessJudge.h"

namespace unit
{
	BrightnessJudge::BrightnessJudge()
	: EndJudge(eBetweenLowerAndUpper), mThresholdLower(0), mThresholdUpper(0), mColorSensorDriver(nullptr)
	{
	}

	BrightnessJudge::BrightnessJudge(ThresholdProcessingMode mode, int thresholdLower, int thresholdUpper, ColorSensorDriver* colorSensorDriver)
	: EndJudge(mode), mThresholdLower(thresholdLower), mThresholdUpper(thresholdUpper), mColorSensorDriver(colorSensorDriver)
	{
	}

	BrightnessJudge::~BrightnessJudge()
	{
		mColorSensorDriver = nullptr;
	}

	bool BrightnessJudge::execute()
	{
		bool judge = true;

		if(mColorSensorDriver != nullptr)
		{
			int brightness = mColorSensorDriver->GetBrightness();
			judge = mThresholdProcessing.execute(mThresholdProcessingMode, brightness, mThresholdLower, mThresholdUpper);
		}
		else
		{
			judge = false;
		}

		return judge;
	}
}  // namespace unit
