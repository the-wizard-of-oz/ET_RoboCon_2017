#include "StartMonitorSequence.h"

namespace unit
{
	StartMonitorSequence::StartMonitorSequence(StartMonitor* startMonitor)
	: ISequence(), mStartMonitor(startMonitor)
	{
	}
	
	StartMonitorSequence::~StartMonitorSequence()
	{
		mStartMonitor = nullptr;
	}
	
	bool StartMonitorSequence::execute()
	{
		return mStartMonitor->execute();
	}
}  // namespace unit
