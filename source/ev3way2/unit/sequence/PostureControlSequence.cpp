#include "PostureControlSequence.h"

namespace unit
{
	PostureControlSequence::PostureControlSequence(PostureController* postureController,
												   eTargetPosture     targetPosture)
	: ISequence(), mPostureController(postureController), mTargetPosture(targetPosture)
	{
	}
	
	PostureControlSequence::~PostureControlSequence()
	{
		mPostureController = nullptr;
	}
	
	bool PostureControlSequence::execute()
	{
		return mPostureController->execute(mTargetPosture);
	}
}  // namespace unit
