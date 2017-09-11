#ifndef UNIT_POSTURE_CONTROL_SEQUENCE_H
#define UNIT_POSTURE_CONTROL_SEQUENCE_H

#include "ISequence.h"
#include "PostureController.h"
#include "TailAngle.h"

namespace unit
{
	class PostureControlSequence
	: public ISequence
	{
		//
	private:
		PostureController* mPostureController;
		eTargetPosture     mTargetPosture;
		
		//
	public:
		PostureControlSequence(PostureController* postureController, eTargetPosture targetPosture);
		virtual ~PostureControlSequence();

		virtual bool execute();
	};
}  // namespace unit
#endif
