#ifndef __USER_I2C_H__
#define __USER_I2C_H__
/*
 * i2c 库
 * thebszk 2024/7/24
 */

#include "sw_i2c.h"
#include "hw_i2c.h"
#include "user_gpio.h"
#include "user_delay.h"

typedef struct
{
    gpio_init_t sda;
    gpio_init_t scl;
    uint32_t delay_us;
} i2c_init_t;

extern sw_i2c_OO_t *sw_i2c1_ptr;
extern sw_i2c_OO_t *sw_i2c2_ptr;

// 实现I2C接口的函数宏,可以自动选择软件I2C或硬件I2C
#define I2C_Scan(i2c_OO_t, scan_addr) _Generic((i2c_OO_t), sw_i2c_OO_t *: SW_I2C_Scan, I2C_TypeDef *: HW_I2C_Scan)(i2c_OO_t, scan_addr);

#define I2C_Read(i2c_OO_t, dev_addr, data, data_length) _Generic((i2c_OO_t), sw_i2c_OO_t *: SW_I2C_Read, I2C_TypeDef *: HW_I2C_Read)(i2c_OO_t, dev_addr, data, data_length);
#define I2C_Write(i2c_OO_t, dev_addr, data, data_length) _Generic((i2c_OO_t), sw_i2c_OO_t *: SW_I2C_Write, I2C_TypeDef *: HW_I2C_Write)(i2c_OO_t, dev_addr, data, data_length);

#define I2C_Read_Byte(i2c_OO_t, dev_addr, data) _Generic((i2c_OO_t), sw_i2c_OO_t *: SW_I2C_Read_Byte, I2C_TypeDef *: HW_I2C_Read_Byte)(i2c_OO_t, dev_addr, data);
#define I2C_Write_Byte(i2c_OO_t, dev_addr, data) _Generic((i2c_OO_t), sw_i2c_OO_t *: SW_I2C_Write_Byte, I2C_TypeDef *: HW_I2C_Write_Byte)(i2c_OO_t, dev_addr, data);

#define I2C_Reg_Read(i2c_OO_t, dev_addr, reg_addr, data, data_length) _Generic((i2c_OO_t), sw_i2c_OO_t *: SW_I2C_Reg_Read, I2C_TypeDef *: HW_I2C_Reg_Read)(i2c_OO_t, dev_addr, reg_addr, data, data_length);
#define I2C_Reg_Write(i2c_OO_t, dev_addr, reg_addr, data, data_length) _Generic((i2c_OO_t), sw_i2c_OO_t *: SW_I2C_Reg_Write, I2C_TypeDef *: HW_I2C_Reg_Write)(i2c_OO_t, dev_addr, reg_addr, data, data_length);
#endif //__I2C_H__
