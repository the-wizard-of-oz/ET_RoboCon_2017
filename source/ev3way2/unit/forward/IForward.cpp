#include "IForward.h"

namespace unit
{
	IForward::IForward()
	: mForward(0)
	{
	}
	
	IForward::~IForward()
	{
	}
	
	int IForward::getForward(bool needUpdate)
	{
		if(needUpdate)
		{
			updateForward();
		}
		
		return mForward;
	}
	
	void IForward::updateForward()
	{
		mForward = calculateForward();
	}
}  // namespace unit
