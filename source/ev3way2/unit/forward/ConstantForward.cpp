#include "ConstantForward.h"

namespace unit
{
	ConstantForward::ConstantForward(float constantForward)
	: IForward(), mConstantForward(constantForward)
	{
	}
	
	ConstantForward::~ConstantForward()
	{
	}
	
	float ConstantForward::calculateForward()
	{
		return mConstantForward;
	}
}  // namespace unit
