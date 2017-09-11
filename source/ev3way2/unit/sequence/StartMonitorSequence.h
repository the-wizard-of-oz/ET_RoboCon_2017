#ifndef UNIT_START_MONITOR_SEQUENCE_H
#define UNIT_START_MONITOR_SEQUENCE_H

#include "ISequence.h"
#include "StartMonitor.h"

namespace unit
{
	class StartMonitorSequence
	: public ISequence
	{
		//
	private:
		StartMonitor* mStartMonitor;
		
		//
	public:
		StartMonitorSequence(StartMonitor* startMonitor);
		virtual ~StartMonitorSequence();

		virtual bool execute();
	};
}  // namespace unit
#endif
