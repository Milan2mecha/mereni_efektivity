#include "HW_control.h"
#include "DMM.h"
#include <stdint.h>

uint8_t DMM_status = 0;

uint8_t DMM_Status(void)
{
    return DMM_status;
}

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
uint8_t DMM_Disable(void){
    if(SWTCH(1,0)!=0){
        return -1;
    }
    if(SWTCH(2,0)!=0){
        return -1;
    }
    if(HW_status() !=1){
        return -1;
    }
    DMM_status = 0;
    return 1;
}


DMM_out DMM_Voltage(uint8_t channel){
    DMM_out out;
    out.status = DMM_status;
    if(out.status != 1){
        return out;
    }
    out.error = HW_status();
    if(out.error != 1){
        return out;
    }
    out.result = HW_voltage(channel);
    return out;
}

DMM_out DMM_Current(uint8_t channel){
    DMM_out out;
    out.status = DMM_status;
    if(out.status != 1){
        return out;
    }
    out.error = HW_status();
    if(out.error != 1){
        return out;
    }
    out.result = HW_current(channel);
    return out;
}
DMM_out DMM_Power(uint8_t channel){
    DMM_out out;
    out.status = DMM_status;
    if(out.status != 1){
        return out;
    }
    out.error = HW_status();
    if(out.error != 1){
        return out;
    }
    out.result = HW_voltage(channel)*HW_current(channel);
    return out;
}