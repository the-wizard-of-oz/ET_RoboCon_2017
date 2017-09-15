#include "GrayTraceTurn.h"

namespace unit
{
	static const int TURN_RANGE = 20;
	
	GrayTraceTurn::GrayTraceTurn(ColorSensorDriver* colorSensorDriver, struct ColorReference* colorReference)
	: BrightTraceTurn(colorSensorDriver), mIsTargetBrightnessUpdated(false), mColorReference(colorReference)
	{
	}
	
	GrayTraceTurn::GrayTraceTurn(ColorSensorDriver* colorSensorDriver,
								 int  brightness,
								 bool isLeftEdgeTraceEnable,
								 int  rightTurnLimit,
								 int  leftTurnLimit,
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
	
	float GrayTraceTurn::calculateTurn()
	{
		float turn = 0.f;
		
		if(!mIsTargetBrightnessUpdated)
		{
			mTargetBrightness = (mColorReference->mBlack + mColorReference->mWhite) / 2;
			mIsTargetBrightnessUpdated = true;
		}
		if(mColorSensorDriver != nullptr)
		{
			int   brightness = mColorSensorDriver->GetBrightness();
			float sign = (mIsLeftEdgeTraceEnable) ? -1.f : 1.f;
			int   denominator = (mColorReference->mWhite - mColorReference->mBlack) / 2;
			if(denominator != 0)
			{
				turn = sign * TURN_RANGE * (brightness - mTargetBrightness) / denominator;
				clip(turn);
			}
		}
		
		return turn;
	}
}  // namespace unit
