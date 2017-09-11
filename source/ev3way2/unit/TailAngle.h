#ifndef UNIT_TAIL_ANGLE_H
#define UNIT_TAIL_ANGLE_H

namespace unit
{
	enum eTargetPosture
	{
		ePostureForStartDash,
		ePostureForRestingInSpeedCourse,
		ePostureForRunningInSpeedCourse
	};
	
	class TailAngle
	{
	private:
		int mForStartDash;
		int mForRestingInSpeedCourse;
		int mForRunningInSpeedCourse;

	public:
		TailAngle();
		TailAngle(int startDash, int resting, int running);
		~TailAngle();

		void SetAngle(eTargetPosture posture, int angle);
		int  GetAngle(eTargetPosture posture);
	};
	
}  // namespace unit
#endif
