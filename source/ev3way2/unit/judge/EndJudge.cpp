#include "EndJudge.h"

namespace unit
{
	EndJudge::EndJudge()
	: mThresholdProcessingMode(eBetweenLowerAndUpper)
	{
	}
	
	EndJudge::EndJudge(ThresholdProcessingMode mode)
	: mThresholdProcessingMode(mode)
	{
	}
	
	EndJudge::~EndJudge()
	{
	}
	
	bool EndJudge::execute()
	{
		return true;
	}
}  // namespace unit
