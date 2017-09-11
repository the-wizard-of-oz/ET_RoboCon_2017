#include "SpeedCoursePlayer.h"

namespace unit
{
	SpeedCoursePlayer::SpeedCoursePlayer()
	{
	}

	SpeedCoursePlayer::~SpeedCoursePlayer()
	{
		std::vector<ISequence*>().swap(mSequence);
	}

	bool SpeedCoursePlayer::execute()
	{
		bool isSpeedCourseCompleted = mSequence.empty();

		if(!isSpeedCourseCompleted)
		{
			bool isSequenceSuccess = (*mSequence.begin())->execute();
			if(isSequenceSuccess)
			{
				delete *(mSequence.begin());
				mSequence.erase(mSequence.begin());
				isSpeedCourseCompleted = mSequence.empty();
			}
		}
		
		return isSpeedCourseCompleted;
	}

	void SpeedCoursePlayer::addSequence(ISequence* iSequence)
	{
		mSequence.push_back(iSequence);
	}
}  // namespace unit
