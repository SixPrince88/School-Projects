#include "my_i2c.h"
#include "my_gpio.h"
#include "my_delay.h"
static void sda_out(bool bit, void* user_data)
{
    i2c_init_t* i2c_group = (i2c_init_t*)user_data;
    gpio_init_t sda={
        .gpio_x=i2c_group->sda.gpio_x,
        .pin_x=i2c_group->sda.pin_x,
        .mode_x=MODE_OOD
    };
    My_GPIO_All_Init(&sda,1);
    GPIO_WriteBit(i2c_group->sda.gpio_x, i2c_group->sda.pin_x, (BitAction)bit);
}

static uint8_t sda_in(void* user_data)
{
    i2c_init_t* x = (i2c_init_t*)user_data;
    gpio_init_t sda={
        .gpio_x=x->sda.gpio_x,
        .pin_x=x->sda.pin_x,
        .mode_x=MODE_INF
    };
    My_GPIO_All_Init(&sda,1);
    return GPIO_ReadInputDataBit(x->sda.gpio_x, x->sda.pin_x);
}

static void scl_out(bool bit, void* user_data)
{
    i2c_init_t* x = (i2c_init_t*)user_data;
    gpio_init_t scl={
        .gpio_x=x->scl.gpio_x,
        .pin_x=x->scl.pin_x,
        .mode_x=MODE_OOD
    };
    My_GPIO_All_Init(&scl,1);
    GPIO_WriteBit(x->scl.gpio_x, x->scl.pin_x, (BitAction)bit);
    if (x->delay_us)
        My_Delay_Us(x->delay_us);
}
// I2C1
i2c_init_t i2c1_gpio = {
    .scl.gpio_x=GPIOB,
    .scl.pin_x=PIN_6,
    .sda.gpio_x=GPIOB,
    .sda.pin_x=PIN_7,
    .delay_us = 5
};

sw_i2c_OO_t sw_i2c1 = {
    .sda_in = sda_in,
    .scl_out = scl_out,
    .sda_out = sda_out,
    .user_data = (void*)&i2c1_gpio,
};

// I2C_OLED
i2c_init_t oled_gpio = {
    .scl.gpio_x=GPIOA,
    .scl.pin_x=PIN_12,
    .sda.gpio_x=GPIOA,
    .sda.pin_x=PIN_15,
    .delay_us = 0
};

sw_i2c_OO_t sw_i2c_oled = {
    .sda_in = sda_in,
    .scl_out = scl_out,
    .sda_out = sda_out,
    .user_data = (void*)&oled_gpio,
};

sw_i2c_OO_t* sw_i2c1_ptr = &sw_i2c1;
sw_i2c_OO_t* sw_i2c_oled_ptr = &sw_i2c_oled;
