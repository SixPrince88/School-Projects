#ifndef __HW_I2C_H__
#define __HW_I2C_H__
#include "stdint.h"
#include "stdbool.h"
#include "stm32f10x.h"
#include "my_gpio.h"
#include "my_clock.h"

void HW_I2C_Init(I2C_TypeDef* I2Cx);

uint8_t HW_I2C_Scan(I2C_TypeDef* I2Cx, uint8_t* scan_addr);

uint8_t  HW_I2C_Read(I2C_TypeDef* I2Cx, uint8_t addr, uint8_t* data, uint8_t data_length);
uint8_t HW_I2C_Write(I2C_TypeDef* I2Cx, uint8_t addr, const uint8_t* data, uint8_t data_length);

uint8_t HW_I2C_Reg_Read(I2C_TypeDef* I2Cx, uint8_t dev_addr, uint8_t mem_addr, uint8_t* data, uint8_t data_length);
uint8_t HW_I2C_Reg_Write(I2C_TypeDef* I2Cx, uint8_t dev_addr, uint8_t mem_addr, const uint8_t* data, uint8_t data_length);

#endif
