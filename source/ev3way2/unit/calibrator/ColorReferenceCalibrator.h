#ifndef UNIT_COLOR_REFERENCE_CALIBRATOR_H
#define UNIT_COLOR_REFERENCE_CALIBRATOR_H

#include "ICalibrator.h"
#include "ColorSensorDriver.h"
#include "ColorReference.h"

namespace unit
{
	class ColorReferenceCalibrator
	: public ICalibrator
	{
		//
	private:
		ColorSensorDriver* mColorSensorDriver;
		ColorReference*    mColorReference;
		
		//
	public:
		ColorReferenceCalibrator(TouchSensorMonitor* touchSensorMonitor, LCD* lcd,
								 ColorSensorDriver*  colorSensorDriver,  ColorReference* colorReference);
		virtual ~ColorReferenceCalibrator();

		virtual bool execute();
	};
}  // namespace unit
#endif
