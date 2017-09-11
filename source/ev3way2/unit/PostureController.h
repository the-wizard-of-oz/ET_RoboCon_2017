#ifndef UNIT_POSTURE_CONTROLLER_H
#define UNIT_POSTURE_CONTROLLER_H

#include "TailController.h"
#include "TailAngle.h"

namespace unit
{
	class PostureController
	{
	private:
		TailController* mTailController;
		TailAngle*      mTailAngle;
		
	public:
		PostureController(TailController* tailController, TailAngle* tailAngle);
		~PostureController();

		bool execute(eTargetPosture targetPosture);
	};
}  // namespace unit
#endif
