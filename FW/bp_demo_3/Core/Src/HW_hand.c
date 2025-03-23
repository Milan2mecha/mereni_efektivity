#include "gpio.h"
#include "i2c.h"
#include "ADS121X.h"
#include "HW_hand.h"
#include "tim.h"
#include "DMM.h"
#include "display.h"

#define PROT1 GPIOB,GPIO_PIN_12
#define PROT2 GPIOB,GPIO_PIN_14
#define STAV_IN GPIOA,GPIO_PIN_3
#define STAV_OUT GPIOA,GPIO_PIN_5
#define RIZENI_IN GPIOA,GPIO_PIN_4
#define RIZENI_OUT GPIOA,GPIO_PIN_6
#define RELE1 GPIOB,GPIO_PIN_13
#define RELE2 GPIOB,GPIO_PIN_15

const float CurrKoef[2][2][3] = {{{0.0004,0.5168,-0.0002},{0.0008,2.5362,-0.0126}},{{0.0004,0.5168,-0.0002},{0.0008,2.5362,-0.0126}}}; //rozsah1A, rozsah5A -> absolutní,lineární,kvadratický
const float VoltKoef[2][3] = {{0.0708,15.122,-0.0688},{0.0708,15.122,-0.0688}}; //absolutní,lineární,kvadratický

uint8_t range[]={0,0}; //0=1A,1=5A
uint8_t rangeOVF[]={0,0};//přetečení rozsahu
uint8_t range_down_flag[]={0,0};

extern DMM_set set_running;

/*blokující delay s časovačem*/
void Delay_TIM(uint16_t time){
	time *= 40;
	uint16_t start = __HAL_TIM_GET_COUNTER(&htim1);
	while(__HAL_TIM_GET_COUNTER(&htim1)!=((start+time)%10000)){
		__NOP();
	}
}
//vrací hodnotu renge flagu pro vyhudnocení v mainu
uint8_t Range_down_flag(uint8_t channel)
{
    return range_down_flag[channel];
}
//přepne kanál zpět do 1A módu
void Range_down(uint8_t channel){
    if(channel == 0){
        range[0]=0;
        HAL_GPIO_WritePin(PROT2,1);
        Delay_TIM(5);
        HAL_GPIO_WritePin(RELE2,0);
        range_down_flag[0]=0;
        Delay_TIM(10);
        HAL_GPIO_WritePin(PROT2,0);

        return;
    }
    if(channel ==1){
        range[1]=0;
        HAL_GPIO_WritePin(PROT1,1);
        Delay_TIM(5);
        HAL_GPIO_WritePin(RELE1,0);
        
        range_down_flag[1]=0;
        Delay_TIM(10);
        HAL_GPIO_WritePin(PROT1,0);
        return;
    }
}

int8_t HW_switch(uint8_t channel, int8_t status){
    if(channel == 1){
        if(HAL_GPIO_ReadPin(STAV_IN) == 1){
            HAL_GPIO_WritePin(RIZENI_IN, status);
            return 1;
        }else{
            HAL_GPIO_WritePin(RIZENI_IN, 0);
            return -1;
        }
    }
    else if(channel == 2){
        if(HAL_GPIO_ReadPin(STAV_OUT) == 1){
            HAL_GPIO_WritePin(RIZENI_OUT, status);
            return 1;
        }else{
            HAL_GPIO_WritePin(RIZENI_OUT, 0);
            return -1;
        }
    }
    else{
        return -1;
    }
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if(GPIO_Pin == GPIO_PIN_1){
        //if(HAL_GPIO_ReadPin(RIZENI_IN)){
            if(range[0]==0){
            	Delay_TIM(5);
                HAL_GPIO_WritePin(PROT2,1);
                range[0]=1;
                HAL_GPIO_WritePin(RELE2,1);
                Delay_TIM(30);//10ms rychlost sepnutí relé
                HAL_GPIO_WritePin(PROT2,0);
                return;
            }else{
                HAL_GPIO_WritePin(PROT2,1);
                rangeOVF[0]=1;
                return;
            }
       /* }else{
            return;
        }*/
	}
    if(GPIO_Pin == GPIO_PIN_0){
       // if(HAL_GPIO_ReadPin(RIZENI_OUT)){
            if(range[1]==0){
            	Delay_TIM(5);
                //Je na 1A rozsahu, přepíná na 5A
                HAL_GPIO_WritePin(PROT1,1);
                HAL_GPIO_WritePin(RELE1,1);
                range[1]=1;
                Delay_TIM(30);//10ms rychlost sepnutí relé
                HAL_GPIO_WritePin(PROT1,0);
                return;
            }else{
                //Je na 5A rozsahu, přezkratuje zapíše registr
                HAL_GPIO_WritePin(PROT1,1);
                rangeOVF[1]=1;
                return;
            }
	}
    if(GPIO_Pin == GPIO_PIN_3){
    	//set_running.status=0;
    	//HW_switch(2,0);
    	//HW_switch(1,0);
    }
    if(GPIO_Pin == GPIO_PIN_5){
    	//set_running.status=0;
    	//HW_switch(2,0);
    	//HW_switch(1,0);
    }
}


uint8_t HW_range(uint8_t channel)
{
	return range[channel];
}

uint8_t HW_status(void){
    if(HAL_GPIO_ReadPin(STAV_IN) == 0){
        HAL_GPIO_WritePin(RIZENI_IN, 0);
        return 1;
    }
    if(HAL_GPIO_ReadPin(STAV_OUT) == 0){
        HAL_GPIO_WritePin(RIZENI_OUT, 0);
        return 1;
    }
    if((rangeOVF[0]==1) || (rangeOVF[1]==1)){
        return 2;
    }
    return 0;
}

uint8_t HW_init(void){
    //Nastaví rozsah
    HAL_GPIO_WritePin(RELE1, 0);
    HAL_GPIO_WritePin(RELE2, 0);
    //reset PROT
    HAL_GPIO_WritePin(PROT1, 1);
    HAL_GPIO_WritePin(PROT2, 1);
    HAL_Delay(10);
    HAL_GPIO_WritePin(PROT1, 0);
    HAL_GPIO_WritePin(PROT2, 0);
    ADS121X_init();
    ADS121X_cal();
    return 0;
}



float HW_voltage(uint8_t channel){
    ADS121X_MUX((channel*2)+1, AGND);
    float tmp = ADS121X_Voltage(ADS121X_meas_sg(), 0, 0);
    float out = (tmp*tmp*VoltKoef[channel][2])+(tmp*VoltKoef[channel][1])+VoltKoef[channel][0];
    return out;
}

float HW_current(uint8_t channel){

    ADS121X_MUX((channel*2), AGND);
    float tmp = ADS121X_Voltage(ADS121X_meas_sg(), 0, 0);
    float out = (tmp*tmp*CurrKoef[channel][range[channel]][2])+(tmp*CurrKoef[channel][range[channel]][1])+CurrKoef[channel][range[channel]][0];
    if(range[channel]&&(out<0.75f)){
        range_down_flag[channel]=1;
    }
    return out;
}

