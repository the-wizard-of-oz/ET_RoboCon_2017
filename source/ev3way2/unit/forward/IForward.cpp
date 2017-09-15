#include "IForward.h"

namespace unit
{
	IForward::IForward()
	: mForward(0.f)
	{
	}
	
	IForward::~IForward()
	{
	}
	
	float IForward::getForward(bool needUpdate)
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
