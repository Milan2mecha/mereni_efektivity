#include <stdint.h>

uint8_t SWTCH (uint8_t channel, int8_t status);
uint8_t HW_status(void);
double HW_voltage(uint8_t channel);
double HW_current(uint8_t channel);