#include "BrightTraceTurn.h"

namespace unit
{
	static const int   BRIGHTNESS_DEFAULT = 30;
	static const float RIGHT_TURN_LIMIT = 20.f;
	static const float LEFT_TURN_LIMIT = -20.f;
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
	
	BrightTraceTurn::BrightTraceTurn(ColorSensorDriver* colorSensorDriver,
									 int brightness,
									 bool isLeftEdgeTraceEnable,
									 float rightTurnLimit,
									 float LeftTurnLimit)
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
	
	float BrightTraceTurn::calculateTurn()
	{
		float turn = 0.f;

		if(mColorSensorDriver != nullptr)
		{
			int   brightness = mColorSensorDriver->GetBrightness();
			float sign = (mIsLeftEdgeTraceEnable) ? -1.f : 1.f;
			turn = sign * P_GAIN * (brightness - mTargetBrightness);
			clip(turn);
		}
		
		return turn;
	}
	
	void BrightTraceTurn::clip(float& turn)
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
