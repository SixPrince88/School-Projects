#ifndef __USART_H
#define __USART_H
#include <stdarg.h>
#include <stdio.h>
#include "stm32f10x.h"
#include "my_gpio.h"
#include "hw_signal.h"

#define usart_type USART_TypeDef *
#define MODE_RX USART_Mode_Rx
#define MODE_TX USART_Mode_Tx
#define MODE_RXTX USART_Mode_Rx|USART_Mode_Tx
typedef struct 
{
	gpio_init_t tx;
	gpio_init_t rx;
	usart_type usart_x;
	uint32_t baudrate;
	uint16_t mode_x;
}usart_init_t;

typedef struct {
	uint8_t cmd;
	uint8_t data1;
	uint8_t data2;
	uint16_t data3;
	uint32_t data4;
}serial_data_groupS;

void My_Serial_Init(usart_init_t usart);
void My_Serial_SendByte(usart_type usart_x,uint8_t Byte);
void My_Serial_SendString(usart_type usart_x,char*string);
void My_Serial_printf(usart_type usart_x,char* format, ...);
uint8_t My_Serial_GetRxFlag(void);
void USART1_Control(void);

#endif
