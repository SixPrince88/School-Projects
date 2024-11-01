#ifndef __HW_QEI_H__
#define __HW_QEI_H__
#include "stm32f10x.h"
#include "my_gpio.h"
#include "my_tim.h"
typedef struct
{
    int16_t l_speed;
    int16_t r_speed;
    int32_t l_distance;
    int32_t r_distance;
} qei_info_t;
extern qei_info_t qei_group;

void HW_QEI_Init(void);
void HW_QEI_Update(void);
void HW_QEI_Reset(void);

#endif
