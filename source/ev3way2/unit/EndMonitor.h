#ifndef UNIT_END_MONITOR_H
#define UNIT_END_MONITOR_H

#include <vector>
#include "EndJudge.h"

namespace unit
{
	class EndMonitor
	{
	private:
		std::vector<EndJudge*> mEndJudges;

	public:
		EndMonitor();
		~EndMonitor();
		
		bool execute();
		void addEndJudge(EndJudge* endJudge);
	};
}  // namespace unit
#endif
