#ifndef UNIT_NEVER_END_JUDGE_H
#define UNIT_NEVER_END_JUDGE_H

#include "EndJudge.h"

namespace unit
{
	class NeverEndJudge
	: public EndJudge
	{
	public:
		NeverEndJudge();
		virtual ~NeverEndJudge();
		
		virtual bool execute();
	};
}  // namespace unit
#endif
