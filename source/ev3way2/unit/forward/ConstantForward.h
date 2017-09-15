#ifndef UNIT_CONSTANT_FORWARD_H
#define UNIT_CONSTANT_FORWARD_H

#include "IForward.h"

namespace unit
{
	class ConstantForward
	: public IForward
	{
	private:
		float mConstantForward;
		
		//
	public:
		ConstantForward(float constantForward);
		virtual ~ConstantForward();

		virtual float calculateForward();
	};
}  // namespace unit
#endif
