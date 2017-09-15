#include "CompassJudge.h"

namespace unit
{
	CompassJudge::CompassJudge()
	: EndJudge(), mThresholdLower(0.f), mThresholdUpper(0.f), mCompass(nullptr)
	{
	}
	
	CompassJudge::CompassJudge(ThresholdProcessingMode mode,
							   float thresholdLower, float thresholdUpper, Compass* compass)
	: EndJudge(mode), mThresholdLower(thresholdLower), mThresholdUpper(thresholdUpper), mCompass(compass)
	{
	}
	
	CompassJudge::~CompassJudge()
	{
	}
	
	bool CompassJudge::execute()
	{
		bool judge = true;
		
		if(mCompass != nullptr)
		{
			float direction = mCompass->getDirection();
			judge = mThresholdProcessing.execute(mThresholdProcessingMode,
												 direction, mThresholdLower, mThresholdUpper);
		}
		else
		{
			judge = false;
		}
		
		return judge;
	}
}  // namespace unit
