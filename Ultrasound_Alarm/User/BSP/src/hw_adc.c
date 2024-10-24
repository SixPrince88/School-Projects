#include "hw_adc.h"
static uint16_t adc_value[2]={0};//ADC值组
void HW_ADC_Init(void){
    gpio_init_t adc_pin[] = {
	    {GPIOA,PIN_4,MODE_AIN},
	    {GPIOA,PIN_5,MODE_AIN},
    };
    adc_init_t adc_group[] = {
        {.adc_Channelx = ADC_Channel_4,.rank=RANK1,.sampletime=SampleTime_239_5},
        {.adc_Channelx = ADC_Channel_5,.rank=RANK2,.sampletime=SampleTime_239_5},
    };
    dma_init_t dma={
        .channel_x = DMA1_Channel1,
        .buff_size = 2,
        .direction = P2M,
        .m_addr=(uint32_t)adc_value,
        .m_inc_state = M_Addr_Inc,
        .m_data_size = M_Size_HalfWord,
        .p_addr = (uint32_t)&ADC1->DR,
        .p_inc_state = P_No_Addr_Inc,
        .p_data_size = P_Size_Word,
    };
    My_GPIO_All_Init(adc_pin,2);
    My_ADC_All_Init(ADC1,2,adc_group,adc_value,dma);
}
