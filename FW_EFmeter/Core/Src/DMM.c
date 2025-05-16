#include "HW_hand.h"
#include "DMM.h"
#include <stdint.h>
#include <float.h>



const DMM_set defaultSet = {0,0,0,20,0,{1,1,1,1}};    //výchozí nastavení
DMM_set set_running = defaultSet;   //inicializace
volatile float data_last[2][2];     //buffer posledních naměřených hodnot


//pomocná funkce zjišťující zda je zařízení v defaultním nastavení
uint8_t nDefaltQ(){
    if(set_running.autoRange!=defaultSet.autoRange){
        return 1;
    }
    if(set_running.sampleRate!=defaultSet.sampleRate){
        return 1;
    }
    if(set_running.continous!=defaultSet.continous){
        return 1;
    }
    return 0;
}
//Naství při běhu zařízení do defaultního režimu
void setdefault()
{
    DMM_SRate(defaultSet.sampleRate);
    set_running.autoRange = defaultSet.autoRange;
    set_running.continous = defaultSet.continous;
}
//funkce vracející aktuální nastavení DMM
DMM_set DMM_Status(void)
{
    return set_running;
}
//Zapnutí DMM
uint8_t DMM_Enable(void)
{
	HW_init();
    HAL_Delay(100);
        //calori_disable
    HW_switch(1,1);
    HAL_Delay(180);
    HW_switch(2,1);
    set_running = defaultSet;
    set_running.mode = 1;
    set_running.status = 1;
    return 1;
}
//Vypnutí DMM
uint8_t DMM_Disable(void){
    HW_switch(1,0);
    HW_switch(2,0);
    set_running.mode = 0;
    set_running.status = 0;
    return 1;
}

//Zapnutí BTES
uint8_t BTES_Enable(void)
{
    DMM_Disable();
	HW_init();
    set_running = defaultSet;
    set_running.mode = 2;
    set_running.status = 1;
    return 1;
}

/*-------------------------------------------*/
/*          Ovládání kanálů BTES             */
/*-------------------------------------------*/
//OFF
uint8_t BTES_OFF(){
    if((set_running.status==0)||(set_running.mode!=2)){
        return 0;
    }
    HW_switch(1,0);
    HW_switch(2,0);
    return 1;
}
//IN
uint8_t BTES_IN(){
    if((set_running.status==0)||(set_running.mode!=2)){
        return 0;
    }
    BTES_OFF();
    HAL_Delay(100);
    return HW_switch(1,1);

}
//OUT
uint8_t BTES_OUT(){
    if((set_running.status==0)||(set_running.mode!=2)){
        return 0;
    }
    BTES_OFF();
    return HW_switch(2,1);
}
/*-------------------------------------------*/
/*          Měření                           */
/*-------------------------------------------*/

//Napětí
DMM_out DMM_Voltage(uint8_t channel){
    DMM_out out;
    DMM_set tmp;
    uint8_t tmpf = nDefaltQ();
    if(tmpf){
        tmp = set_running;
        setdefault();
    }
    out.status = set_running.status;
    if(out.status != 1){
        return out;
    }
    out.error = HW_status();
    if(out.error != 0){
        return out;
    }
    out.result = (double) HW_voltage(channel);
    if(tmpf){
        set_running= tmp;
    }
    return out;
}
//Proud
DMM_out DMM_Current(uint8_t channel){
    DMM_out out;
    DMM_set tmp;
    uint8_t tmpf = nDefaltQ();
    if(tmpf){
        tmp = set_running;
        setdefault();
    }
    out.status = set_running.status;
    if(out.status != 1){
        return out;
    }
    out.error = HW_status();
    if(out.error != 0){
        return out;
    }
    out.result = (double) HW_current(channel);
    if(tmpf){
        set_running= tmp;
    }
    return out;
}
//Výkon
DMM_out DMM_Power(uint8_t channel){
    DMM_out out;
    DMM_set tmp;
    uint8_t tmpf = nDefaltQ();
    if(tmpf){
        tmp = set_running;
        setdefault();
    }
    out.status = set_running.status;
    if(out.status != 1){
        return out;
    }
    out.error = HW_status();
    if(out.error != 0){
        return out;
    }
    out.result =(double)  (HW_voltage(channel)*HW_current(channel));
    if(tmpf){
        set_running= tmp;
    }
    return out;
}


/*-------------------------------------------*/
/*       Fetch subsystem                     */
/*-------------------------------------------*/


DMM_out DMM_Fetch_volt(uint32_t channel){
    DMM_out out;
    if(set_running.continous){
        out.status = set_running.status;
        out.error = HW_status();
        if(out.error != 0){
            return out;
        }
        out.result =(double) data_last[0][channel];
        return out;
    }else{
        out.status = set_running.status;
        out.error = HW_status();
        if(out.error != 0){
            return out;
        }
        data_last[0][channel] =  HW_voltage(channel);
        out.result = (double)data_last[0][channel];
        return out;
    }
}

DMM_out DMM_Fetch_current(uint32_t channel){
    DMM_out out;
    if(set_running.continous){
        out.status = set_running.status;
        out.error = HW_status();
        if(out.error != 0){
            return out;
        }
        out.result = data_last[1][channel];
        return out;
    }else{
        out.status = set_running.status;
        out.error = HW_status();
        if(out.error != 0){
            return out;
        }
        data_last[1][channel] =  HW_current(channel);
        out.result = data_last[1][channel];
        return out;
    }
}



/*-------------------------------------------*/
/*       Nastavování parametrů měření        */
/*-------------------------------------------*/

//nastavení samplerate
void DMM_SRate(uint16_t SR){
    if(HW_SR((uint16_t)SR)){
        
    }else{
    set_running.sampleRate =(uint16_t) SR;
    }
    return;
}


