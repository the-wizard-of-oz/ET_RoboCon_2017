#include "BalancingController.h"
#include "../balancer.h"

namespace unit
{
	BalancingController::BalancingController()
	{
	}

	BalancingController::~BalancingController()
	{
	}

	void BalancingController::Balance_Init()
	{
		balance_init();
	}

	void BalancingController::Balance_Control(float args_cmd_forward, float args_cmd_turn,
											  float args_gyro,        float args_gyro_offset,
											  float args_theta_m_l,   float args_theta_m_r,
											  float args_battery,
											  signed char *ret_pwm_l, signed char *ret_pwm_r)
	{
		balance_control(args_cmd_forward, args_cmd_turn, args_gyro, args_gyro_offset, args_theta_m_l, args_theta_m_r, args_battery, ret_pwm_l, ret_pwm_r);
	}
}  // namespace unit
