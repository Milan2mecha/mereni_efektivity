#include "gpio.h"
#include "i2c.h"

uint8_t HW_status(void);
uint8_t HW_init(void);
int8_t HW_switch(uint8_t channel, int8_t status);
float HW_voltage(uint8_t channel);
float HW_current(uint8_t channel);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);