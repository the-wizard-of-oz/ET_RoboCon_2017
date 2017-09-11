#include "TailAngle.h"

namespace unit
{
	static const int restingInSpeedCourseDefault = 93;
	static const int startDashDefault            = restingInSpeedCourseDefault + 1;
	static const int runningInSpeedCourseDefault = restingInSpeedCourseDefault - 45;
	
	TailAngle::TailAngle()
	: mForStartDash(startDashDefault), mForRestingInSpeedCourse(restingInSpeedCourseDefault), mForRunningInSpeedCourse(runningInSpeedCourseDefault)
	{
	}

	TailAngle::TailAngle(int startDash, int resting, int running)
	: mForStartDash(startDash), mForRestingInSpeedCourse(resting), mForRunningInSpeedCourse(running)
	{
	}

	TailAngle::~TailAngle()
	{
	}

	void TailAngle::SetAngle(eTargetPosture posture, int angle)
	{
		switch(posture)
		{
			case ePostureForStartDash:
				mForStartDash = angle;
				break;
			case ePostureForRestingInSpeedCourse:
				mForRestingInSpeedCourse = angle;
				break;
			case ePostureForRunningInSpeedCourse:
				mForRunningInSpeedCourse = angle;
				break;
			default:
				break;
		}
	}
	
	int TailAngle::GetAngle(eTargetPosture posture)
	{
		int angle = 0;
		
		switch(posture)
		{
			case ePostureForStartDash:
				angle = mForStartDash;
				break;
			case ePostureForRestingInSpeedCourse:
				angle = mForRestingInSpeedCourse;
				break;
			case ePostureForRunningInSpeedCourse:
				angle = mForRunningInSpeedCourse;
				break;
			default:
				break;
		}
		
		return angle;
	}
}  // namespace unit
