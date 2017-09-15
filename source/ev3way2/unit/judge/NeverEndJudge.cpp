#include "NeverEndJudge.h"

namespace unit
{
	NeverEndJudge::NeverEndJudge()
	: EndJudge()
	{
	}
	
	NeverEndJudge::~NeverEndJudge()
	{
	}
	
	bool NeverEndJudge::execute()
	{
		return false;
	}
}  // namespace unit
