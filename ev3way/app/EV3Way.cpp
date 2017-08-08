#include "EV3Way.h"

namespace app
{
	EV3Way::EV3Way(unit::ModeMonitor modeMonitor)
	: mModeMonitor(modeMonitor)
	{
	}

	void EV3Way::execute()
	{
		mModeMonitor.execute();
	}
}  // namespace app
