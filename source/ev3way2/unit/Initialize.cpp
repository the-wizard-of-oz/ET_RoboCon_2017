#include "Initialize.h"

namespace unit
{
	Initialize::Initialize(PostureController* postureController)
	: mPostureController(postureController)
	{
	}
	
	Initialize::~Initialize()
	{
		mPostureController = nullptr;
	}

	bool Initialize::execute()
	{
		return mPostureController->execute(ePostureForRestingInSpeedCourse);
	}
}  // namespace unit
