#ifndef UNIT_CALIBRATOR_H
#define UNIT_CALIBRATOR_H

#include "ColorJudge.h"
#include "LCD.h"

namespace unit
{
	class Calibrator
	{
	private:
		ColorJudge* mColorJudge;
		LCD mLCD;

	public:
		Calibrator(ColorJudge* colorJudge);
		~Calibrator();
		bool execute();
	};
}  // namespace unit
#endif
