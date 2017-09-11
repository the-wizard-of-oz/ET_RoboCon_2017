#include "GrayTraceTurn.h"

namespace unit
{
	static const int TURN_RANGE = 20;
	
	GrayTraceTurn::GrayTraceTurn(ColorSensorDriver* colorSensorDriver, struct ColorReference* colorReference)
	: BrightTraceTurn(colorSensorDriver), mIsTargetBrightnessUpdated(false), mColorReference(colorReference)
	{
	}
	
	GrayTraceTurn::GrayTraceTurn(ColorSensorDriver* colorSensorDriver,
								 int brightness,
								 bool isLeftEdgeTraceEnable,
								 int rightTurnLimit,
								 int leftTurnLimit,
								 struct ColorReference* colorReference)
	: BrightTraceTurn(colorSensorDriver,
					  brightness,
					  isLeftEdgeTraceEnable,
					  rightTurnLimit,
					  leftTurnLimit),
	  mIsTargetBrightnessUpdated(false),
	  mColorReference(colorReference)
	{
	}
	
	GrayTraceTurn::~GrayTraceTurn()
	{
		mColorReference = nullptr;
	}
	
	int GrayTraceTurn::calculateTurn()
	{
		int turn = 0;
		
		if(!mIsTargetBrightnessUpdated)
		{
			mTargetBrightness = (mColorReference->mBlack + mColorReference->mWhite) / 2;
			mIsTargetBrightnessUpdated = true;
		}
		if(mColorSensorDriver != nullptr)
		{
			int brightness = mColorSensorDriver->GetBrightness();
			int sign = (mIsLeftEdgeTraceEnable) ? -1 : 1;
			int denominator = (mColorReference->mWhite - mColorReference->mBlack) / 2;
			if(denominator != 0)
			{
				turn = sign * TURN_RANGE * (brightness - mTargetBrightness) / denominator;
				clip(turn);
			}
		}
		
		return turn;
	}
}  // namespace unit
