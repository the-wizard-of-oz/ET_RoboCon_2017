#ifndef UNIT_COLOR_REFERENCE_H
#define UNIT_COLOR_REFERENCE_H

namespace unit
{
	enum colorType
	{
		eBlack,
		eWhite,
		eGray
	};
		
	struct ColorReference
	{
	public:
		int mBlack;
		int mWhite;
		int mGray;

	public:
		ColorReference() : mBlack(0), mWhite(0), mGray(0) {}
	};
}  // namespace unit
#endif
