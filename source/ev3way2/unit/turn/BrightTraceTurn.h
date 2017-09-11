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
		int  mRightTurnLimit;
		int  mLeftTurnLimit;
	
	//
	public:
		BrightTraceTurn();
		BrightTraceTurn(ColorSensorDriver* colorSensorDriver);
		BrightTraceTurn(ColorSensorDriver* colorSensorDriver, int brightness, bool isLeftEdgeTraceEnable, int rightTurnLimit, int LeftTurnLimit);
		virtual ~BrightTraceTurn();

		virtual int calculateTurn();
		
	protected:
		void clip(int& turn);
	};
}  // namespace unit
#endif
