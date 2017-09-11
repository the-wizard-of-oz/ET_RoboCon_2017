#ifndef UNIT_I_TURN_H
#define UNIT_I_TURN_H

namespace unit
{
	class ITurn
	{
	//
	private:
		int mTurn;
	
	//
	public:
		ITurn();
		virtual ~ITurn();

		int  getTurn(bool needUpdate = false);
		void updateTurn();
		virtual int calculateTurn() = 0;
	};
}  // namespace unit
#endif
