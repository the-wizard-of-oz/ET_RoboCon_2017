#ifndef UNIT_DISTANCE_JUDGE_H
#define UNIT_DISTANCE_JUDGE_H

#include "EndJudge.h"
#include "DistanceMeter.h"

namespace unit
{
	class DistanceJudge
	: public EndJudge
	{
	private:
		float mThresholdLower;
		float mThresholdUpper;
		DistanceMeter* mDistanceMeter;

	public:
		DistanceJudge();
		DistanceJudge(ThresholdProcessingMode mode, float thresholdLower, float thresholdUpper, DistanceMeter* distanceMeter);
		~DistanceJudge();
		
		bool execute();
	};
}  // namespace unit
#endif
