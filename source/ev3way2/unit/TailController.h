#ifndef UNIT_TAIL_CONTROLLER_H
#define UNIT_TAIL_CONTROLLER_H

#include "MotorDriver.h"

namespace unit
{
	namespace tailControl
	{
		enum eCallMode
		{
			eSingleCall,
			eCycleCall
		};

		enum eControlSpeed
		{
			eLowSpeed,
			eMiddleSpeed,
			eHighSpeed
		};

		enum eTerminateMode
		{
			eLessThanTargetAngle,
			eEqualToTargetAngle,
			eLargerThanTargetAngle
		};
	}
	
	class TailController
	{
	private:
		bool isTailMotorInitialized;
		MotorDriver* mTailMotorDriver;

	public:
		TailController();
		TailController(MotorDriver* tailMotorDriver);
		~TailController();

		bool execute(int targetAngle, tailControl::eCallMode callMode, tailControl::eControlSpeed controlSpeed, tailControl::eTerminateMode terminateMode);

	private:
		bool  isTailControlTerminate(int currentAngle, int targetAngle, tailControl::eTerminateMode terminateMode);
		float getGain(tailControl::eControlSpeed controlSpeed);
	};
}  // namespace unit
#endif
