#ifndef UNIT_POSTURE_CONTROLLER_H
#define UNIT_POSTURE_CONTROLLER_H

#include "ev3api.h"
#include "Motor.h"

namespace unit
{
	class PostureController
	{
	private:
		int mTailAngleResting;
		int mTailAngleRunning;
		ev3api::Motor* mTailMotor;

	public:
		PostureController();
		~PostureController();
		void initializeMotor();
		bool shiftToRestingPosture();
		bool shiftToRunningPosture();
	private:
		bool shiftPosture(float targetDegree);
	};
}  // namespace unit
#endif
