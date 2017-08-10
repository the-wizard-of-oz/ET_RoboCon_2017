#ifndef APP_EV3_WAY_H
#define APP_EV3_WAY_H

#include "../unit/ModeMonitor.h"

namespace app
{
	class EV3Way
	{
	private:
		unit::ModeMonitor mModeMonitor;

	public:
		EV3Way(unit::ModeMonitor modeMonitor);
		void execute();
	};
}  // namespace app
#endif
