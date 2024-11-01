#include "hw_qei.h"

void HW_QEI_Init(void){
    gpio_init_t gpio_group={GPIOA, PIN_1|PIN_2|PIN_6|PIN_7,MODE_INF};
    My_GPIO_All_Init(&gpio_group, 1);
    My_TIM_Encoder_Start(TIM2);
    My_TIM_Encoder_Start(TIM3);
}
void HW_QEI_Update(void){
    qei_group.l_speed=(int16_t)TIM_GetCounter(TIM2);
		TIM_SetCounter(TIM2,0);
    qei_group.r_speed=(int16_t)TIM_GetCounter(TIM3);
		TIM_SetCounter(TIM3,0);
    qei_group.l_distance+=qei_group.l_speed;
    qei_group.r_distance+=qei_group.r_speed;
}
void HW_QEI_Reset(void){
    qei_group.l_distance=0;
    qei_group.r_distance=0;
}
