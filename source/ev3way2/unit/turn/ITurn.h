#ifndef UNIT_I_TURN_H
#define UNIT_I_TURN_H

namespace unit
{
	class ITurn
	{
	//
	private:
		float mTurn;
	
	//
	public:
		ITurn();
		virtual ~ITurn();

		float getTurn(bool needUpdate);
		void  updateTurn();
		virtual float calculateTurn() = 0;
	};
}  // namespace unit
#endif
