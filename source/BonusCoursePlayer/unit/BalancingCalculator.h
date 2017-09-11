#ifndef UNIT_BALANCING_CALCULATOR_H
#define UNIT_BALANCING_CALCULATOR_H

namespace unit
{
	class BalancingCalculator
	{
	public:
		BalancingCalculator();
		void initializeBalancer();
		void calculate(float args_cmd_forward, float args_cmd_turn, float args_gyro, float args_gyro_offset, float args_theta_m_l, float args_theta_m_r, float args_battery, signed char* ret_pwm_l, signed char* ret_pwm_r);
	};
}  // namespace unit
#endif
