#ifndef __HW_FD07_3_H
#define __HW_FD07_3_H
#include "my_gpio.h"
#include "my_exti.h"
#include "my_tim.h"
#include "my_delay.h"
#include "my_serial.h"
#include "lowpass_filter.h"
#include "hw_oled.h"

#define FD07_3_NUM 3         // 6个传感器
#define FD07_3_MAX_NUM 6     // 最大传感器数量
#define FD07_3_BUFFER_SIZE 5 // 每个传感器缓存5个数据

void HW_FD07_3_Init(void);
void FD07_3_Start(void);
void FD07_3_Get_Dist(void);
void FD07_3_Send_Data(void);

#endif
