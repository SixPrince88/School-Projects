#include "string.h"
#include "user_delay.h"
#include "user_clock.h"
#include "user_nvic.h"
#include "user_i2c.h"
#include "hw_signal.h"
#include "hw_timestamp.h"
#include "hw_oled.h"
#include "hw_serial.h"
#include "hw_fd07_3.h"
timestamp_t timestamp = {0};	// 时间戳组
extern uint8_t fd07_3_updateflag;	// 更新标志位
void User_HW_Init(void)
{
	nvic_init_t nvic_group[] = {
		{USART1_IRQn, 0, 0},
		{TIM3_IRQn, 1, 0},
		{EXTI15_10_IRQn, 2, 0},
	};
	usart_init_t usart1_t = {
		.tx = {.gpio_x = GPIOA, .pin_x = PIN_9, .mode_x = MODE_APP},
		.rx = {.gpio_x = GPIOA, .pin_x = PIN_10, .mode_x = MODE_IPU},
		.usart_x = USART1,
		.mode_x = MODE_RXTX,
		.baudrate = 115200,
	};
	RCC_AHBPeriphClockCmd(AHB_DMA1, ENABLE);
	RCC_APB1PeriphClockCmd(APB1_USART2 | APB1_USART3 | APB1_TIM2 | APB1_TIM3 | APB1_TIM4 | APB1_I2C1, ENABLE);
	RCC_APB2PeriphClockCmd(APB2_AFIO | APB2_GPIOA | APB2_GPIOB | APB2_GPIOC | APB2_TIM1 | APB2_USART1 | APB2_ADC1, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	User_NVIC_All_Init(NVIC_PriorityGroup_2, nvic_group, sizeof(nvic_group) / sizeof(nvic_group[0]));
	User_Serial_Init(usart1_t);
}
int main(void)
{
	User_Delay_Ms(1000);
	User_HW_Init();
	HW_Signal_Init();
	HW_FD07_3_Init();
	HW_OLED_Init();
	// 主函数流程
	while (1)
	{
		u32 time = 10000; // 超时时间
		fd07_3_updateflag = 0x00;
		TIM_SetCounter(TIM3, 0);
		FD07_3_Start();
		while (fd07_3_updateflag == 0x07 && --time) // 等待所有传感器数据更新
			;
		if (time != 0) // 超时则不更新数据
		{
			FD07_3_Get_Dist();
			HW_USART1_Control();
		}
	}
}
