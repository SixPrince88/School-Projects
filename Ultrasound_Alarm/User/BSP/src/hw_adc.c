#include "hw_adc.h"
static uint16_t adc_value[2] = {0}; // ADC值组
void HW_ADC_Init(void)
{
    gpio_init_t adc_pin[] = {
        {GPIOA, PIN_4, MODE_AIN},
        {GPIOA, PIN_5, MODE_AIN},
    };
    adc_init_t adc1 = {
        .adc_x= ADC1,
		.channel_group[0]={.channel_x= ADC_Channel_4, .rank=1},
		.channel_group[1]={.channel_x= ADC_Channel_5, .rank=2},
        .adc_value= adc_value,
        .dma_state= true
    };

    My_GPIO_All_Init(adc_pin, 2);
    My_ADC_All_Init(adc1);
}
void Sensor1_Get(void){
    
}
void Sensor2_Get(void){
    
}
void Sensor3_Get(void){
    
}
