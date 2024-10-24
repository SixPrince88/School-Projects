#include "my_adc.h"
#include "my_dma.h"
/*
	*@brief:ADC初始化
	*@param:adc_x:ADC1/ADC2
	*@param:ad_num:通道数
	*@param:ad_group:通道组
	*@retval:无
*/
void My_ADC_Init(adc_type adc_x,uint8_t adc_num,adc_init_t adc_group[])
{
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	ADC_DeInit(adc_x);
	ADC_InitTypeDef sys;
	ADC_StructInit(&sys);
	sys.ADC_Mode = ADC_Mode_Independent;
	sys.ADC_DataAlign = ADC_DataAlign_Right;
	sys.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	sys.ADC_ContinuousConvMode = ENABLE;
	sys.ADC_ScanConvMode = ENABLE;
	sys.ADC_NbrOfChannel = adc_num;
	ADC_Init(adc_x, &sys);
	//批量设置通道
	for(uint8_t i=0;i<adc_num;i++)
	{
		if(adc_group[i].adc_Channelx==0)continue;
		ADC_RegularChannelConfig(adc_x,adc_group[i].adc_Channelx,adc_group[i].rank,adc_group[i].sampletime);
	}
}
/*
	*@brief:ADC启动
	*@param:adc_x:ADC1/ADC2
	*@param:ad_num:通道数
	*@param:ad_group:通道组
	*@param:ad_value_group:存放ADC值的数组
	*@retval:无
*/
void My_ADC_All_Init(adc_type adc_x,uint8_t adc_num,adc_init_t adc[],uint16_t adc_value[],dma_init_t dma)
{
	My_ADC_Init(adc_x,adc_num,adc);
	My_DMA_Init(dma);
	ADC_Cmd(adc_x, ENABLE);//开启ADC
	ADC_ResetCalibration(adc_x);
	while (ADC_GetResetCalibrationStatus(adc_x));//复位校准
	ADC_StartCalibration(adc_x);
	while (ADC_GetCalibrationStatus(adc_x));//校准完成
	ADC_SoftwareStartConvCmd(adc_x, ENABLE);
	
	ADC_DMACmd(adc_x,ENABLE);
}
