#include <stdio.h>
#include "my_serial.h"
// 以数据包为单位的长度为15的缓冲区
#define BUFFER_MAX_LEN 15
serial_data_groupS *user_data_ptr = NULL;	  // 实际使用的数据包指针
serial_data_groupS rx_buffer[BUFFER_MAX_LEN]; // 缓冲区
uint8_t rxbuff_index_head = 0;				  // 缓冲区头索引
uint8_t rxBuff_index_tail = 0;				  // 缓冲区尾索引
uint8_t rx_data_offset = 0;					  // 地址偏移量
/*
 *@brief:usart初始化
 *@param:usartGroupS usart
 *@return:void
 */
void My_Serial_Init(usart_init_t usart)
{
	My_GPIO_All_Init(&usart.tx, 1);
	My_GPIO_All_Init(&usart.rx, 1);
	USART_InitTypeDef sys;
	sys.USART_BaudRate = usart.baudrate;
	sys.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	sys.USART_Mode = usart.mode_x;
	sys.USART_Parity = USART_Parity_No;
	sys.USART_StopBits = USART_StopBits_1;
	sys.USART_WordLength = USART_WordLength_8b;
	USART_Init(usart.usart_x, &sys);
	USART_ITConfig(usart.usart_x, USART_IT_RXNE, ENABLE);
	USART_Cmd(usart.usart_x, ENABLE);
}
void My_Serial_SendByte(usart_type usart_x, uint8_t Byte)
{
	USART_SendData(usart_x, Byte); // 填充数据至 USART1的DR寄存器

	// USART_FLAG_TXE: 发送寄存器为空标志位。对USART_DR的写操作时，将该位清零。
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
		; // 等待发送完成
}
void My_Serial_SendString(usart_type usart_x, char *string)
{
	uint8_t i = 0;
	for (i = 0; string[i] != '\0'; i++)
	{
		My_Serial_SendByte(usart_x, string[i]);
	}
}
void My_Serial_printf(usart_type usart_x, char *format, ...)
{
	char String[100] = {0};
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	My_Serial_SendString(usart_x, String);
}
/*
 *@brief:获取接收数据标志位
 *@param:uint8_t
 *@return:1表示接收到数据，0表示没有数据
 */
uint8_t My_Serial_GetRxFlag(void)
{
	// 如果接收缓冲区头不等于接收缓冲区尾，则表示接收到数据
	if (rxbuff_index_head != rxBuff_index_tail)
	{
		// 实际使用的数据包指针指向接收缓冲区头索引
		user_data_ptr = &rx_buffer[rxbuff_index_head];
		// 头索引加1
		rxbuff_index_head = (rxbuff_index_head + 1) % BUFFER_MAX_LEN;
		return 1;
	}
	else
	{
		return 0;
	}
}
uint8_t rx_data = 0; // 接收数据
extern bool fd07_3_send_flag;
void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		rx_data = USART_ReceiveData(USART1);
	}
}
void USART1_Control(void)
{
	switch (rx_data)
	{
	case 'Y':
		fd07_3_send_flag = true; // 数据发送开始
		break;
	case 'N':
		fd07_3_send_flag = false; // 数据发送结束
		break;
	case 'A':
		HW_Signal_On(ALARM_TURN_LEFT); // 左转警报开启
		break;
	case 'a':
		HW_Signal_Off(ALARM_TURN_LEFT); // 左转警报关闭
		break;
	case 'B':
		HW_Signal_On(ALARM_FORWARD); // 前进警报开启
		break;
	case 'b':
		HW_Signal_Off(ALARM_FORWARD); // 前进警报关闭
		break;
	case 'C':
		HW_Signal_On(ALARM_DINGDING); // 叮叮警报开启
		break;
	case 'c':
		HW_Signal_Off(ALARM_DINGDING); // 叮叮警报关闭
		break;
	case 'D':
		HW_Signal_On(ALARM_TURN_RIGHT); // 右转警报开启
		break;
	case 'd':
		HW_Signal_Off(ALARM_TURN_RIGHT); // 右转警报关闭
		break;
	}
}
