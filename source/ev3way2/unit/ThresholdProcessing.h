#ifndef UTIL_THRESHOLD_PROCESSING_H
#define UTIL_THRESHOLD_PROCESSING_H

namespace unit
{
	enum ThresholdProcessingMode
	{
		eLessThanLower,
		eBetweenLowerAndUpper,
		eGreaterThanUpper
	};
	
	class ThresholdProcessing
	{
	public:
		template <typename T>
		bool execute(ThresholdProcessingMode mode, T value, T thresholdLower, T thresholdUpper);
	};

	template <typename T>
	bool ThresholdProcessing::execute(ThresholdProcessingMode mode, T value, T thresholdLower, T thresholdUpper)
	{
		bool isInRange = true;
		
		switch(mode)
		{
			case eLessThanLower:
				isInRange = (value < thresholdLower);
				break;
			case eBetweenLowerAndUpper:
				isInRange = ((thresholdLower <= value) && (value <= thresholdUpper));
				break;
			case eGreaterThanUpper:
				isInRange = (thresholdUpper < value);
				break;
			default:
				isInRange = false;
				break;
		}
 
		return isInRange;
	}
}	// namespace unit
#endif
