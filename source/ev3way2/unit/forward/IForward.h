#ifndef UNIT_I_FORWARD_H
#define UNIT_I_FORWARD_H

namespace unit
{
	class IForward
	{
	//
	private:
		int mForward;
	
	//
	public:
		IForward();
		virtual ~IForward();

		int  getForward(bool needUpdate = false);
		void updateForward();

	private:
		virtual int calculateForward() = 0;
	};
}  // namespace unit
#endif
