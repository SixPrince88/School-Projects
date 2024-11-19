#include "user_adc.h"
#include "user_dma.h"
/*
 *@brief:ADC初始化
 *@param:adc_x:ADC1/ADC2
 *@param:ad_num:通道数
 *@param:ad_group:通道组
 *@retval:无
 */
void User_ADC_Init(adc_init_t adc)
{
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	ADC_DeInit(adc.adc_x);
	ADC_InitTypeDef sys;
	ADC_StructInit(&sys);
	sys.ADC_Mode = ADC_Mode_Independent;
	sys.ADC_DataAlign = ADC_DataAlign_Right;
	sys.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	sys.ADC_ContinuousConvMode = ENABLE;
	sys.ADC_ScanConvMode = ENABLE;
	sys.ADC_NbrOfChannel = ADC_NUM;
	ADC_Init(adc.adc_x, &sys);
	// 批量设置通道
	for (uint8_t i = 0; i < ADC_NUM; i++)
	{
		if (adc.channel_group[i].channel_x == 0)
			continue;
		ADC_RegularChannelConfig(adc.adc_x, adc.channel_group[i].channel_x, adc.channel_group[i].rank, ADC_SampleTime_239Cycles5);
	}
}
/*
 *@brief:ADC批量初始化
 *@param:adc:adc初始化结构体
 *@retval:无
 */
void User_ADC_All_Init(adc_init_t adc)
{
	User_ADC_Init(adc);
	if (adc.dma_state)
	{
		dma_init_t dma = {
			.channel_x = DMA1_Channel1,
			.buff_size = 2,
			.direction = P2M,
			.m_addr = (uint32_t)adc.adc_value,
			.m_inc_state = M_Addr_Inc,
			.m_data_size = M_Size_HalfWord,
			.p_addr = (uint32_t)&ADC1->DR,
			.p_inc_state = P_No_Addr_Inc,
			.p_data_size = P_Size_Word,
		};
		User_DMA_Init(dma);
	}
	ADC_Cmd(adc.adc_x, ENABLE); // 开启ADC
	ADC_ResetCalibration(adc.adc_x);
	while (ADC_GetResetCalibrationStatus(adc.adc_x))
		; // 复位校准
	ADC_StartCalibration(adc.adc_x);
	while (ADC_GetCalibrationStatus(adc.adc_x))
		; // 校准完成
	ADC_SoftwareStartConvCmd(adc.adc_x, ENABLE);
	if (adc.dma_state)
	{
		ADC_DMACmd(adc.adc_x, ENABLE);
	}
}
