#ifndef __USER_ADC_H
#define __USER_ADC_H
#include "stm32f10x.h"
#include "stdbool.h"
#include "user_dma.h"
#define adc_type ADC_TypeDef *
#define SampleTime_1_5 ADC_SampleTime_1Cycles5
#define SampleTime_7_5 ADC_SampleTime_7Cycles5
#define SampleTime_13_5 ADC_SampleTime_13Cycles5
#define SampleTime_28_5 ADC_SampleTime_28ycles5
#define SampleTime_41_5 ADC_SampleTime_41ycles5
#define SampleTime_71_5 ADC_SampleTime_71Cycles5
#define SampleTime_239_5 ADC_SampleTime_239Cycles5

#define ADC_NUM 2

typedef struct
{
    uint8_t channel_x;
    uint8_t rank;
} adc_channel_t;

typedef struct
{
    adc_type adc_x;
    adc_channel_t channel_group[ADC_NUM];
    uint16_t *adc_value;
    bool dma_state;
} adc_init_t;
typedef enum
{
    RANK1 = 1,
    RANK2,
    RANK3,
    RANK4,
    RANK5,
    RANK6,
    RANK7,
    RANK8,
    RANK9,
    RANK10,
    RANK11,
    RANK12,
    RANK13,
    RANK14,
    RANK15
} rank_t;
void User_ADC_All_Init(adc_init_t adc_x);

#endif
