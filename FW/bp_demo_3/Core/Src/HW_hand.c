#include "gpio.h"
#include "i2c.h"
#include "ADS121X.h"
#include "HW_hand.h"
#include "tim.h"
#include "DMM.h"
#include "Display.h"
#include "eeprom.h"
#include "eeprom_loader.h"
#include <float.h>

#define PROT1 GPIOB,GPIO_PIN_12
#define PROT2 GPIOB,GPIO_PIN_14
#define STAV_IN GPIOA,GPIO_PIN_3
#define STAV_OUT GPIOA,GPIO_PIN_5
#define RIZENI_IN GPIOA,GPIO_PIN_4
#define RIZENI_OUT GPIOA,GPIO_PIN_6
#define RELE1 GPIOB,GPIO_PIN_13
#define RELE2 GPIOB,GPIO_PIN_15

volatile float CurrKoef[2][2][3] = {{{0,1,0},{0,1,0}},{{0,1,0},{0,1,0}}}; //rozsah1A, rozsah5A -> absolutní,lineární,kvadratický
volatile float VoltKoef[2][3] = {{0,1,0},{0,1,0}}; //absolutní,lineární,kvadratický

uint8_t range[]={0,0}; //0=1A,1=5A
uint8_t rangeOVF[]={0,0};//přetečení rozsahu
uint8_t range_down_flag[]={0,0}; //příznak splnění podínek pro snížení rozsahu

extern DMM_set set_running;


/*----------------------------------------------*/
/*                 Pomocné funkce               */
/*----------------------------------------------*/


/*načítání dat z eeprom do proměnných*/
void load_EEPROM(){
   for(uint8_t i = 0;i<3;i++){
        VoltKoef[0][i] = read_form_eeprom(U1_ee+(4*i));
    }
    for(uint8_t i = 0;i<3;i++){
        VoltKoef[1][i] = read_form_eeprom(U2_ee+(4*i));
    }
    for(uint8_t i = 0;i<3;i++){
        CurrKoef[0][0][i] = read_form_eeprom(I11_ee+(4*i));
    }
    for(uint8_t i = 0;i<3;i++){
        CurrKoef[0][1][i] = read_form_eeprom(I12_ee+(4*i));
    }
    for(uint8_t i = 0;i<3;i++){
        CurrKoef[1][0][i] = read_form_eeprom(I21_ee+(4*i));
    }
    for(uint8_t i = 0;i<3;i++){
        CurrKoef[1][1][i] = read_form_eeprom(I22_ee+(4*i));
    }
        
}

double get_koef(uint8_t U_I, uint8_t channel, uint8_t rozsah, uint8_t koef){
   if(U_I == 0){
        //napeti
        return (double)VoltKoef[channel][koef];
    }else{
        return (double)CurrKoef[channel][rozsah][koef];
    }
}

/*blokující delay s časovačem*/
void Delay_TIM(uint16_t time){
	time *= 40;
	uint16_t start = __HAL_TIM_GET_COUNTER(&htim1);
	while(__HAL_TIM_GET_COUNTER(&htim1)!=((start+time)%10000)){
		__NOP();
	}
}

/*----------------------------------------------*/
/*                Inicializace                  */
/*----------------------------------------------*/


uint8_t HW_init(void){
    //Nastaví rozsah
    HAL_GPIO_WritePin(RELE1, 0);
    HAL_GPIO_WritePin(RELE2, 0);
    range[0]=0;
    range[1]=0;
    rangeOVF[0]=0;
    rangeOVF[1]=0;
    //reset PROT
    HAL_GPIO_WritePin(PROT1, 1);
    HAL_GPIO_WritePin(PROT2, 1);
    HAL_Delay(10);
    HAL_GPIO_WritePin(PROT1, 0);
    HAL_GPIO_WritePin(PROT2, 0);
    ADS121X_init();
    ADS121X_cal();
    load_EEPROM();
    return 0;
}

/*----------------------------------------------*/
/*                 Autorange                    */
/*----------------------------------------------*/


//vrací hodnotu range flagu pro vyhudnocení v mainu
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

//funkce přerušení pro přepínání na vyšší rozsah
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if(GPIO_Pin == GPIO_PIN_1){
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
	}
    if(GPIO_Pin == GPIO_PIN_0){    
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

}

/*----------------------------------------------*/
/*                 Měření                       */
/*----------------------------------------------*/
//volty blokující 
float HW_voltage(uint8_t channel){
    ADS121X_MUX((channel*2)+1, AGND);
    float tmp = ADS121X_Voltage(ADS121X_meas_sg(), 0, 0);
    float out = (tmp*tmp*VoltKoef[channel][2])+(tmp*VoltKoef[channel][1])+VoltKoef[channel][0];
    return out;
}
//proud blokující
float HW_current(uint8_t channel){
    ADS121X_MUX((channel*2), AGND);
    float tmp = ADS121X_Voltage(ADS121X_meas_sg(), 0, 0);
    float out = (tmp*tmp*CurrKoef[channel][range[channel]][2])+(tmp*CurrKoef[channel][range[channel]][1])+CurrKoef[channel][range[channel]][0];
    if(range[channel]&&(out<0.75f)){
        range_down_flag[channel]=1;
    }
    return out;
}

//sepnutí asynchronního měření napětí
void HW_async_volt_start(uint8_t channel){
    ADS121X_MUX((channel*2)+1, AGND);
    ADS121X_start();
}

//sepnutí asynchronního měření proud
void HW_async_current_start(uint8_t channel){
    ADS121X_MUX((channel*2), AGND);
    ADS121X_start();
}

//vyčtení asynchronního měření
float HW_async_get(uint8_t channel){
    float tmp;
    float out;
    if(ADS121X_ready()!=0){
        tmp = ADS121X_Voltage(ADS121X_Voltage_getAsync(),0,0);
        if(channel%2){
            channel = (channel-1)/2;
            out = (tmp*tmp*CurrKoef[channel][range[channel]][2])+(tmp*CurrKoef[channel][range[channel]][1])+CurrKoef[channel][range[channel]][0]; 
        }else{
            channel = (channel/2);
            out = (tmp*tmp*VoltKoef[channel][2])+(tmp*VoltKoef[channel][1])+VoltKoef[channel][0];
        }
        return out;
    }else{
        tmp = FLT_MAX;
        return tmp;
    }
}

/*----------------------------------------------*/
/*                 Akce                         */
/*----------------------------------------------*/

//spínání vstupních relé
int8_t HW_switch(uint8_t channel, int8_t status){
    if(channel == 1){
        if(HAL_GPIO_ReadPin(STAV_IN) != 0){
            HAL_GPIO_WritePin(RIZENI_IN, status);
            return 1;
        }else{
            HAL_GPIO_WritePin(RIZENI_IN, 0);
            return -1;
        }
    }
    else if(channel == 2){
        if(HAL_GPIO_ReadPin(STAV_OUT) != 0){
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

/*----------------------------------------------*/
/*             Čtení stavů                      */
/*----------------------------------------------*/

//nastavení sample rate
uint8_t HW_SR(uint16_t SR){
    return ADS121X_DR(SR);
}

//nastavení rozsahu na kanálu
uint8_t HW_range(uint8_t channel)
{
	return range[channel];
}


//čtení statusu ochran
uint8_t HW_status(void){
    if(HAL_GPIO_ReadPin(RIZENI_IN) == 1){
        if(HAL_GPIO_ReadPin(STAV_IN) == 0){
            HAL_GPIO_WritePin(RIZENI_IN, 0);
            return 1;
    }
    }
    if(HAL_GPIO_ReadPin(RIZENI_OUT) == 1){
        if(HAL_GPIO_ReadPin(STAV_OUT) == 0){
            HAL_GPIO_WritePin(RIZENI_OUT, 0);
            return 1;
    }}
    if((rangeOVF[0]==1) || (rangeOVF[1]==1)){
        return 2;
    }
    return 0;
}





