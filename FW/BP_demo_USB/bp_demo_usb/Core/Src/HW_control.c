#include "HW_control.h"
#include <stdint.h>

uint8_t SWTCH (uint8_t channel, int8_t status){
    if(channel == 1){
        uint8_t status1 = 0; //simulace vypínače
        status1 = status; //simulace řízení
        if(status1 == status){
            return status1;
        }else{
            return -1;
        }
    }
    else if(channel == 2){
        uint8_t status2 = 0; //simulace vypínače
        status2 = status; //simulace řízení
        if(status2 == status){
            return status2;
        }else{
            return -1;
        }
    }
    return -1;
}

uint8_t HW_status(void){
    return 1;
}
double HW_voltage(uint8_t channel){
    if(channel == 1){
    return 0.12;
    }else{
    return 0.24;
    }
}
double HW_current(uint8_t channel){
    if(channel == 1){
    return 0.3;
    }else{
    return 0.4;
    }
}