#include "DistanceJudge.h"

namespace unit
{
	DistanceJudge::DistanceJudge()
	: EndJudge(), mThresholdLower(0.f), mThresholdUpper(0.f), mDistanceMeter(nullptr)
	{
	}
	
	DistanceJudge::DistanceJudge(ThresholdProcessingMode mode, float thresholdLower, float thresholdUpper, DistanceMeter* distanceMeter)
	: EndJudge(mode), mThresholdLower(thresholdLower), mThresholdUpper(thresholdUpper), mDistanceMeter(distanceMeter)
	{
	}
	
	DistanceJudge::~DistanceJudge()
	{
	}
	
	bool DistanceJudge::execute()
	{
		bool judge = true;
		
		if(mDistanceMeter != nullptr)
		{
			float distance = mDistanceMeter->getDistance();
			judge = mThresholdProcessing.execute(mThresholdProcessingMode, distance, mThresholdLower, mThresholdUpper);
		}
		else
		{
			judge = false;
		}
		
		return judge;
	}
}  // namespace unit
