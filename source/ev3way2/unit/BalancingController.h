#ifndef UNIT_BALANCING_CONTROLLER_H
#define UNIT_BALANCING_CONTROLLER_H

namespace unit
{
	class BalancingController
	{
	public:
		BalancingController();
		~BalancingController();

		void Balance_Init();
		void Balance_Control(float args_cmd_forward, float args_cmd_turn,
							 float args_gyro,        float args_gyro_offset,
							 float args_theta_m_l,   float args_theta_m_r, float args_battery,
							 signed char *ret_pwm_l, signed char *ret_pwm_r);
	};
}  // namespace unit
#endif
