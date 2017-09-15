#ifndef UNIT_GRAY_TRACE_TURN_H
#define UNIT_GRAY_TRACE_TURN_H

#include "BrightTraceTurn.h"
#include "ColorReference.h"

namespace unit
{
	class GrayTraceTurn
	: public BrightTraceTurn
	{
	//
	private:
		bool mIsTargetBrightnessUpdated;
		struct ColorReference* mColorReference;
	
	//
	public:
		GrayTraceTurn(ColorSensorDriver* colorSensorDriver, struct ColorReference* colorReference);
		GrayTraceTurn(ColorSensorDriver* colorSensorDriver,
					  int brightness,
					  bool isLeftEdgeTraceEnable,
					  int rightTurnLimit,
					  int LeftTurnLimit,
					  struct ColorReference* colorReference);
		virtual ~GrayTraceTurn();

		virtual float calculateTurn();
	};
}  // namespace unit
#endif
