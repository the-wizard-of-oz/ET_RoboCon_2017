#ifndef UNIT_COMPASS_JUDGE_H
#define UNIT_COMPASS_JUDGE_H

#include "EndJudge.h"
#include "Compass.h"

namespace unit
{
	class CompassJudge
	: public EndJudge
	{
	private:
		float mThresholdLower;
		float mThresholdUpper;
		Compass* mCompass;

	public:
		CompassJudge();
		CompassJudge(ThresholdProcessingMode mode, float thresholdLower, float thresholdUpper, Compass* compass);
		~CompassJudge();
		
		bool execute();
	};
}  // namespace unit
#endif
