#include "BrightTraceTurn.h"

namespace unit
{
	static const int   BRIGHTNESS_DEFAULT = 30;
	static const int   RIGHT_TURN_LIMIT = 20;
	static const int   LEFT_TURN_LIMIT = -20;
	static const float P_GAIN = 2.5;
	
	BrightTraceTurn::BrightTraceTurn()
	: ITurn(),
	  mColorSensorDriver(nullptr),
	  mTargetBrightness(BRIGHTNESS_DEFAULT),
	  mIsLeftEdgeTraceEnable(true),
	  mRightTurnLimit(RIGHT_TURN_LIMIT),
	  mLeftTurnLimit(LEFT_TURN_LIMIT)
	{
	}
	
	BrightTraceTurn::BrightTraceTurn(ColorSensorDriver* colorSensorDriver)
	: ITurn(),
	  mColorSensorDriver(colorSensorDriver),
	  mTargetBrightness(BRIGHTNESS_DEFAULT),
	  mIsLeftEdgeTraceEnable(true),
	  mRightTurnLimit(RIGHT_TURN_LIMIT),
	  mLeftTurnLimit(LEFT_TURN_LIMIT)
	{
	}
	
	BrightTraceTurn::BrightTraceTurn(ColorSensorDriver* colorSensorDriver, int brightness, bool isLeftEdgeTraceEnable, int rightTurnLimit, int LeftTurnLimit)
	: ITurn(),
	  mColorSensorDriver(colorSensorDriver),
	  mTargetBrightness(brightness),
	  mIsLeftEdgeTraceEnable(isLeftEdgeTraceEnable),
	  mRightTurnLimit(rightTurnLimit),
	  mLeftTurnLimit(LeftTurnLimit)
	{
	}
	
	BrightTraceTurn::~BrightTraceTurn()
	{
		mColorSensorDriver = nullptr;
	}
	
	int BrightTraceTurn::calculateTurn()
	{
		int turn = 0;

		if(mColorSensorDriver != nullptr)
		{
			int brightness = mColorSensorDriver->GetBrightness();
			int sign = (mIsLeftEdgeTraceEnable) ? -1 : 1;
			turn = sign * P_GAIN * (brightness - mTargetBrightness);
			clip(turn);
		}
		
		return turn;
	}
	
	void BrightTraceTurn::clip(int& turn)
	{
		if(turn > mRightTurnLimit)
		{
			turn = mRightTurnLimit;
		}
		if(turn < mLeftTurnLimit)
		{
			turn = mLeftTurnLimit;
		}
	}
}  // namespace unit
