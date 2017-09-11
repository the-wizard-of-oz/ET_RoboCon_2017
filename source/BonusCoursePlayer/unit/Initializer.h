#ifndef UNIT_INITIALIZER_H
#define UNIT_INITIALIZER_H

#include "PostureController.h"

namespace unit
{
	class Initializer
	{
	private:
		PostureController* mTailController;

	public:
		Initializer(PostureController* tailController);
		~Initializer();
		bool execute();
	};
}  // namespace unit
#endif
