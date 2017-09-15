#include "ITurn.h"

namespace unit
{
	ITurn::ITurn()
	: mTurn(0.f)
	{
	}
	
	ITurn::~ITurn()
	{
	}
	
	float ITurn::getTurn(bool needUpdate)
	{
		if(needUpdate)
		{
			updateTurn();
		}
		
		return mTurn;
	}
	
	void ITurn::updateTurn()
	{
		mTurn = calculateTurn();
	}
}  // namespace unit
