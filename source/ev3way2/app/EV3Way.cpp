#include "EV3Way.h"

namespace app
{
	EV3Way::EV3Way(unit::ModeSwitcher* modeSwitcher)
	: mModeSwitcher(modeSwitcher)
	{
	}
	
	EV3Way::~EV3Way()
	{
		mModeSwitcher = nullptr;
	}

	void EV3Way::execute()
	{
		mModeSwitcher->execute();
	}
}  // namespace app
