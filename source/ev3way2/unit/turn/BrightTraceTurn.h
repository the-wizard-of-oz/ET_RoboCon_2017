#ifndef UNIT_BRIGHT_TRACE_TURN_H
#define UNIT_BRIGHT_TRACE_TURN_H

#include "ITurn.h"
#include "ColorSensorDriver.h"

namespace unit
{
	class BrightTraceTurn
	: public ITurn
	{
	//
	protected:
		ColorSensorDriver* mColorSensorDriver;
		int  mTargetBrightness;
		bool mIsLeftEdgeTraceEnable;
		
	private:
		float mRightTurnLimit;
		float mLeftTurnLimit;
	
	//
	public:
		BrightTraceTurn();
		BrightTraceTurn(ColorSensorDriver* colorSensorDriver);
		BrightTraceTurn(ColorSensorDriver* colorSensorDriver, int brightness, bool isLeftEdgeTraceEnable,
						float rightTurnLimit, float LeftTurnLimit);
		virtual ~BrightTraceTurn();

		virtual float calculateTurn();
		
	protected:
		void clip(float& turn);
	};
}  // namespace unit
#endif
