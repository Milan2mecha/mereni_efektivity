#include "HW_hand.h"
#include <stdint.h>



typedef struct{
    uint8_t status;
    int8_t error;
    double result;
}DMM_out;

typedef struct{
    uint8_t status;
    uint8_t autoRange; //0-on 1-off
    uint8_t mode; //0-off 1-dmm 2-btes
    uint16_t sampleRate;
    uint8_t continous;
    uint8_t activeChannels[4];//v ch1,I ch1,V ch2,I_ch2
}DMM_set;

DMM_set DMM_Status(void);
uint8_t DMM_Enable(void);
uint8_t DMM_Disable(void);

DMM_out DMM_Voltage(uint8_t channel);
DMM_out DMM_Current(uint8_t channel);
DMM_out DMM_Power(uint8_t channel);

DMM_out DMM_Fetch_volt(uint32_t channel);
DMM_out DMM_Fetch_current(uint32_t channel);


void DMM_SRate(uint16_t SR);
void DMM_Continous(uint32_t status);
uint8_t DMM_modeContinous();
uint8_t DMM_Asyncsample(uint8_t channel);

