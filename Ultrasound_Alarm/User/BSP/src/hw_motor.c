#include "hw_motor.h"
gpio_init_t motor_pwm_gpio = {
    .gpio_x = GPIOA,
    .pin_x = PIN_8 | PIN_11,
    .mode_x = MODE_APP};
// 注意，电机多个引脚不可以相或，否则电平相同，电机不转动
gpio_init_t motor_l_gpio[] = {
    {.gpio_x = GPIOB, .pin_x = PIN_12, .mode_x = MODE_OPP},
    {.gpio_x = GPIOB, .pin_x = PIN_13, .mode_x = MODE_OPP}};
gpio_init_t motor_r_gpio[] = {
    {.gpio_x = GPIOB, .pin_x = PIN_14, .mode_x = MODE_OPP},
    {.gpio_x = GPIOB, .pin_x = PIN_15, .mode_x = MODE_OPP}};
/*
 * @brief 电机引脚控制
 * @param id 电机编号
 * @param a_out a引脚电平
 * @param b_out b引脚电平
 * @return 无
 */
static void HW_Moter_SetPin(uint8_t id, bool a_out, bool b_out)
{
    switch (id)
    {
    case MOTOR_L:
        GPIO_WriteBit(motor_l_gpio[0].gpio_x, motor_l_gpio[0].pin_x, (BitAction)a_out);
        GPIO_WriteBit(motor_l_gpio[1].gpio_x, motor_l_gpio[1].pin_x, (BitAction)b_out);
        break;
    case MOTOR_R:
        GPIO_WriteBit(motor_r_gpio[0].gpio_x, motor_r_gpio[0].pin_x, (BitAction)a_out);
        GPIO_WriteBit(motor_r_gpio[1].gpio_x, motor_r_gpio[1].pin_x, (BitAction)b_out);
        break;
    }
}
/*
 * @brief 电机初始化
 * @param 无
 * @return 无
 * @note 无
 */
void HW_Motor_Init(void)
{
    timbase_init_t tim1_group = {
        .arr_x = 4800 - 1,
        .psc_x = 1 - 1,
        .tim_x = TIM1,
    };
    oc_init_t motor_oc_group[] = {
        {.tim_x = TIM1, .channel_x = OC_CHANNEL_1},
        {.tim_x = TIM1, .channel_x = OC_CHANNEL_4},
    };
    My_TIM_Base_Init(tim1_group);
    MY_TIM_OC_Start(motor_oc_group, 2);

    My_GPIO_All_Init(&motor_pwm_gpio, 1);
    My_GPIO_All_Init(motor_l_gpio, 2);
    My_GPIO_All_Init(motor_r_gpio, 2);

    HW_Moter_SetPin(MOTOR_L, 1, 1);
    HW_Moter_SetPin(MOTOR_R, 1, 1);
}
/*
 * @brief 设置电机停止模式
 * @param mode 停止模式
 * @return 无
 * @note 无
 */
Moter_Stop_Mode stop_mode = MOTOR_STOP_MODE_BRAKE;
void moter_setStopMode(Moter_Stop_Mode mode)
{
    stop_mode = mode;
}
/*
 * @brief 电机控制
 * @param CCR_L 左电机占空比
 * @param CCR_R 右电机占空比
 * @return 无
 */
void HW_Motor_Run(int16_t CCR_L, int16_t CCR_R)
{
    // 左电机
    if (CCR_L == 0)
    {
        HW_Moter_SetPin(MOTOR_L, stop_mode, stop_mode);
    }
    else
    {
        HW_Moter_SetPin(MOTOR_L, 1, 1);
#ifdef MOTER_DEADBAND
        CCR_L += ((CCR_L > 0) - (CCR_L < 0)) * MOTER_DEADBAND; // 只有用上死区才编译这行代码
#endif
        int16_t Out_L = Limit(CCR_L, -MOTER_MAX_SPEED, MOTER_MAX_SPEED);
        TIM_SetCompare1(TIM1, Out_L);
        HW_Moter_SetPin(MOTOR_L, Out_L < 0, Out_L > 0);
    }
    // 右电机
    if (CCR_R == 0)
    {
        HW_Moter_SetPin(MOTOR_R, stop_mode, stop_mode);
    }
    else
    {
        HW_Moter_SetPin(MOTOR_R, 1, 1);
#ifdef MOTER_DEADBAND
        CCR_R += ((CCR_R > 0) - (CCR_R < 0)) * MOTER_DEADBAND; // 只有用上死区才编译这行代码
#endif
        int16_t Out_R = Limit(CCR_R, -MOTER_MAX_SPEED, MOTER_MAX_SPEED);
        TIM_SetCompare4(TIM1, Out_R);
        HW_Moter_SetPin(MOTOR_R, Out_R > 0, Out_R < 0);
    }
}
