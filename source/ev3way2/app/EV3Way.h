#ifndef APP_EV3_WAY_H
#define APP_EV3_WAY_H

#include "../unit/ModeSwitcher.h"

namespace app
{
	class EV3Way
	{
	private:
		unit::ModeSwitcher* mModeSwitcher;

	public:
		EV3Way(unit::ModeSwitcher* modeSwitcher);
		~EV3Way();
		
		void execute();
	};
}  // namespace app
#endif
