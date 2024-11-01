#ifndef __HW_MOTER_H__
#define __HW_MOTER_H__
#include "stdbool.h"
#include "stm32f10x.h"
#include "my_gpio.h"
#include "my_tim.h"
#include "common.h"
#define MOTER_MAX_SPEED 4800

//#define MOTER_DEADBAND 0

typedef enum {
    MOTOR_L = 0,
    MOTOR_R,
}Motor_id;
typedef enum {
    MOTOR_STOP_MODE_BRAKE = 0,//制动(电机电源线短接,转动阻尼提高)
    MOTOR_STOP_MODE_GLIDE,//滑行(无输入且不短接,正常阻尼)
} Moter_Stop_Mode;

void HW_Motor_Init(void);
void HW_Motor_Run(int16_t CCR_L, int16_t CCR_R);

#endif
