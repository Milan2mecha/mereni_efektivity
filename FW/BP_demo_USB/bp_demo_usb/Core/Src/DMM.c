#include "HW_control.h"
#include "DMM.h"
#include <stdint.h>


uint8_t DMM_Enable(void)
{
        //calori_disable
    if(SWTCH(1,1)!=1){
        return -1;
    }
    if(SWTCH(2,1)!=1){
        return -1;
    }
    if(HW_status() !=1){
        return -1;
    }
    DMM_status = 1;
    return 1;
}

double DMM_voltage(uint8_t channel){
    return HW_voltage(channel);
}

double DMM_current(uint8_t channel){
    return HW_current(channel);
}
double DMM_power(uint8_t channel){
    double out = DMM_current(channel);
    out *= DMM_voltage(channel);
    return out;
}