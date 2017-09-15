#ifndef UNIT_I_FORWARD_H
#define UNIT_I_FORWARD_H

namespace unit
{
	class IForward
	{
	//
	private:
		float mForward;
	
	//
	public:
		IForward();
		virtual ~IForward();

		float getForward(bool needUpdate);
		void  updateForward();

	private:
		virtual float calculateForward() = 0;
	};
}  // namespace unit
#endif
