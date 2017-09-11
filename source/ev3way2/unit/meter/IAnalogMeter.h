#ifndef UNIT_I_ANALOG_METER_H
#define UNIT_I_ANALOG_METER_H

namespace unit
{
	class IAnalogMeter
	{
	protected:
		int mPreviousRightEncoderCount;
		int mPreviousLeftEncoderCount;

	public:
		IAnalogMeter();
		IAnalogMeter(int previousRightEncoderCount, int previousLeftEncoderCount);
		virtual ~IAnalogMeter();

		void initPrevEncoderCount(int previousRightEncoderCount, int previousLeftEncoderCount);
		virtual void update(int previousRightEncoderCount, int previousLeftEncoderCount) = 0;
	};
}  // namespace unit
#endif
