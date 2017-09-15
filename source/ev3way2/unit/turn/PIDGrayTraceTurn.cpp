#include "PIDGrayTraceTurn.h"
#include "globalResource.h"

namespace unit
{
	static const float TIME_PERIOD      = 0.004;
	static const float TURN_UPPER_LIMIT = 100.f;
	static const float TURN_LOWER_LIMIT = -100.f;
	
	PIDGrayTraceTurn::PIDGrayTraceTurn(ColorSensorDriver* colorSensorDriver,
									   struct ColorReference* colorReference,
									   float kp,
									   float ki,
									   float kd)
	: ITurn(), mColorSensorDriver(colorSensorDriver), mColorReference(colorReference), mKp(kp), mKi(ki), mKd(kd)
	{
	}
	
	PIDGrayTraceTurn::~PIDGrayTraceTurn()
	{
		mColorSensorDriver = nullptr;
		mColorReference    = nullptr;
	}

	float PIDGrayTraceTurn::calculateTurn()
	{
		static int  targetBrightness = 0;
		static bool isTargetBrightnessUpdated = false;
		if(!isTargetBrightnessUpdated)
		{
			targetBrightness = (mColorReference->mBlack + mColorReference->mWhite) / 2;
			isTargetBrightnessUpdated = true;
		}
		
		static float diffOld  = 0.f;
		static float diffNew  = 0.f;
		static float integral = 0.f;

		diffOld = diffNew;
		diffNew = mColorSensorDriver->GetBrightness() - targetBrightness;
		integral += (diffNew + diffOld) / 2.f * TIME_PERIOD;

		float p = mKp * diffNew;
		float i = mKi * integral;
		float d = mKd * (diffNew - diffOld) / TIME_PERIOD;

		float signForLeftEdgeTravel = -1.f;
		float turn = signForLeftEdgeTravel * (p + i + d);
		clip(turn);
		
		{
			char buf[128] = {0};
			sprintf(buf, "p:%f, i:%f, d:%f, ", p, i, d);
			gBluetoothLogger->log(buf, strlen(buf));
			sprintf(buf, "targetBrightness:%d, currentBrightness:%f\r\n",
					targetBrightness, diffNew + targetBrightness);
			gBluetoothLogger->log(buf, strlen(buf));
		}
		
		return turn;
	}
	
	void PIDGrayTraceTurn::clip(float& turn)
	{
		if(turn > TURN_UPPER_LIMIT)
		{
			turn = TURN_UPPER_LIMIT;
		}
		if(turn < TURN_LOWER_LIMIT)
		{
			turn = TURN_LOWER_LIMIT;
		}
	}
}  // namespace unit
