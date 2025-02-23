#include "HW_control.h"
#include <stdint.h>
int8_t DMM_status;



uint8_t DMM_Enable(void);
double DMM_voltage(uint8_t channel);
double DMM_current(uint8_t channel);
double DMM_power(uint8_t channel);


