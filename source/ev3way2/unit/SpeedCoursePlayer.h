#ifndef UNIT_SPEED_COURSE_PLAYER_H
#define UNIT_SPEED_COURSE_PLAYER_H

#include <vector>
#include "ISequence.h"

namespace unit
{
	class SpeedCoursePlayer
	{
		//
	private:
		std::vector<ISequence*> mSequence;
		
		//
	public:
		SpeedCoursePlayer();
		~SpeedCoursePlayer();

		bool execute();
		void addSequence(ISequence* iSequence);
	};
}  // namespace unit
#endif
