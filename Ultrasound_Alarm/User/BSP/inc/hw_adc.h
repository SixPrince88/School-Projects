#ifndef __HW_ADC_H__
#define __HW_ADC_H__
#include "my_gpio.h"
#include "my_adc.h"
#include "my_dma.h"

void HW_ADC_Init(void);
void sensor1_get(void);
void sensor2_get(void);
void sensor3_get(void);
#endif
