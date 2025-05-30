#include "gpio.h"
#include "i2c.h"



uint8_t HW_range(uint8_t channel);
uint8_t HW_status(void);
uint8_t HW_init(void);
int8_t HW_switch(uint8_t channel, int8_t status);
double HW_voltage(uint8_t channel);
double HW_current(uint8_t channel);
void Range_down(uint8_t channel);
uint8_t Range_down_flag(uint8_t channel);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
uint8_t HW_SR(uint16_t SR);
float HW_async_get(uint8_t channel);
void HW_async_current_start(uint8_t channel);
void HW_async_volt_start(uint8_t channel);
void load_EEPROM();
double get_koef(uint8_t U_I, uint8_t channel, uint8_t rozsah, uint8_t koef);