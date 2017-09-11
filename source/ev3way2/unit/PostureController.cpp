#include "PostureController.h"

namespace unit
{
	PostureController::PostureController(TailController* tailController, TailAngle* tailAngle)
	: mTailController(tailController), mTailAngle(tailAngle)
	{
	}

	PostureController::~PostureController()
	{
		mTailController = nullptr;
		mTailAngle      = nullptr;
	}

	bool PostureController::execute(eTargetPosture posture)
	{
		return mTailController->execute(mTailAngle->GetAngle(posture),
										tailControl::eSingleCall,
										tailControl::eLowSpeed,
										tailControl::eTerminateMode::eEqualToTargetAngle);
	}
}  // namespace unit
