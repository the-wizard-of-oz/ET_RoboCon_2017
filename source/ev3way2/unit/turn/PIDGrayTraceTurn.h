#ifndef UNIT_PID_GRAY_TRACE_TURN_H
#define UNIT_PID_GRAY_TRACE_TURN_H

#include "ITurn.h"
#include "ColorSensorDriver.h"
#include "ColorReference.h"

namespace unit
{
	class PIDGrayTraceTurn
	: public ITurn
	{
		//
	private:
		ColorSensorDriver*     mColorSensorDriver;
		struct ColorReference* mColorReference;
		int  mTargetBrightness;
		bool mIsTargetBrightnessUpdated;
		
		float mKp;
		float mKi;
		float mKd;
		
		//
	public:
		PIDGrayTraceTurn(ColorSensorDriver* colorSensorDriver, struct ColorReference* colorReference,
						 float kp, float ki, float kd);
		virtual ~PIDGrayTraceTurn();

		virtual float calculateTurn();
		
	private:
		void clip(float& turn);
	};
}  // namespace unit
#endif
