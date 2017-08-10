#include "Calibrator.h"

namespace unit
{
	Calibrator::Calibrator(ColorJudge* colorJudge)
	: mColorJudge(colorJudge)
	{
	}

	Calibrator::~Calibrator()
	{
		mColorJudge = nullptr;
	}

	bool Calibrator::execute()
	{
		bool isSuccess = true;
		mColorJudge->updateDeterminationValues();
		int black, white, gray;
		mColorJudge->getDeterminationValues(black, white, gray);
		{
			char str[32] = {0};
			sprintf(str, "Black:%3d, White:%3d, Gray:%3d", black, white, gray);
			mLCD.display(str);
		}

		return isSuccess;
	}
}  // namespace unit
