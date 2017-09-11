#include <cstddef>
#include "EndMonitor.h"

namespace unit
{
	EndMonitor::EndMonitor()
	{
	}
	
	EndMonitor::~EndMonitor()
	{
		for(auto it = mEndJudges.begin(); it != mEndJudges.end(); ++it)
		{
			delete *it;
		}
		mEndJudges.clear();
		std::vector<EndJudge*>().swap(mEndJudges);
	}
	
	bool EndMonitor::execute()
	{
		bool isEnd = true;
		
		for(auto it = mEndJudges.begin(); it != mEndJudges.end(); ++it)
		{
			isEnd &= (*it)->execute();
		}
		
		return isEnd;
	}
	
	void EndMonitor::addEndJudge(EndJudge* endJudge)
	{
		mEndJudges.push_back(endJudge);
	}
}  // namespace unit
