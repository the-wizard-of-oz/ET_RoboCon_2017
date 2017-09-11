#ifndef LOOK_UP_GATE_PLAYER_H
#define LOOK_UP_GATE_PLAYER_H

namespace unit
{
	class LookUpGatePlayer{
	private:
		int mState;
	public:
		LookUpGatePlayer();
		~LookUpGatePlayer();

		bool execute();
	};


}


#endif
