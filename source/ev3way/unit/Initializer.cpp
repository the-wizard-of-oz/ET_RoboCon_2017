#include "Initializer.h"

namespace unit
{
	Initializer::Initializer(PostureController* tailController)
	: mTailController(tailController)
	{
	}
	
	Initializer::~Initializer()
	{
		mTailController = nullptr;
	}

	bool Initializer::execute()
	{
		mTailController->initializeMotor();
		bool isComplete = false;
		while(!isComplete)
		{
			isComplete = mTailController->shiftToRestingPosture();
		}
		return true;
	}
}  // namespace unit
