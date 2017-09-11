#ifndef UNIT_INITIALIZE_H
#define UNIT_INITIALIZE_H

#include "PostureController.h"

namespace unit
{
	class Initialize
	{
	//
	private:
		PostureController* mPostureController;

	//
	public:
		Initialize(PostureController* postureController);
		~Initialize();
		
		bool execute();
	};
}  // namespace unit
#endif
