#ifndef UNIT_I_TRAVE_H
#define UNIT_I_TRAVE_H

#include "MotorController.h"

namespace unit
{
	class ITravel
	{
	//
	protected:
		MotorController* mMotorController;

	//
	public:
		ITravel(MotorController* motorController);
		virtual ~ITravel();

		virtual bool execute() = 0;
	};
}  // namespace unit
#endif
