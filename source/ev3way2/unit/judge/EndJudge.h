#ifndef UNIT_END_JUDGE_H
#define UNIT_END_JUDGE_H

#include "ThresholdProcessing.h"

namespace unit
{
	class EndJudge
	{
	protected:
		ThresholdProcessingMode mThresholdProcessingMode;
		ThresholdProcessing mThresholdProcessing;
		
	public:
		EndJudge();
		EndJudge(ThresholdProcessingMode mode);
		virtual ~EndJudge();
		
		virtual bool execute();
	};
}  // namespace unit
#endif
