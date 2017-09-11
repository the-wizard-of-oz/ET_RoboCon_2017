#ifndef UNIT_I_SEQUENCE_H
#define UNIT_I_SEQUENCE_H

#include "EndMonitor.h"

namespace unit
{
	class ISequence
	{
	public:
		ISequence();
		virtual ~ISequence();

		virtual bool execute() = 0;
	};
}  // namespace unit
#endif
