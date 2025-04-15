#include "HW_hand.h"
#include "DMM.h"
#include <stdint.h>
#include <float.h>



const DMM_set defaultSet = {0,0,20,0,{0,0,0,0}};    //výchozí nastavení
DMM_set set_running = defaultSet;   //inicializace
double data_last[2][2];     //buffer posledních naměřených hodnot


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
        //calori_disable
    if(HW_switch(1,1)!=1){
        return -1;
    }
    if(HW_switch(2,1)!=1){
        return -1;
    }
    if(HW_status() !=0){
        return -1;
    }
    set_running = defaultSet;
    set_running.status = 1;
    return 1;
}
//Vypnutí DMM
uint8_t DMM_Disable(void){
    if(HW_switch(1,0)!=1){
        return -1;
    }
    if(HW_switch(2,0)!=1){
        return -1;
    }
    if(HW_status() !=0){
        return -1;
    }
    set_running.status = 0;
    return 1;
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
        out.result = data_last[0][channel];
        return out;
    }else{
        out.status = set_running.status;
        out.error = HW_status();
        if(out.error != 0){
            return out;
        }
        data_last[0][channel] = (double) HW_voltage(channel);
        out.result = data_last[0][channel];
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
        data_last[1][channel] = (double) HW_current(channel);
        out.result = data_last[1][channel];
        return out;
    }
}



/*-------------------------------------------*/
/*       Nastavování parametrů měření        */
/*-------------------------------------------*/

//zapnutí vypnutí continous
void DMM_Continous(uint32_t status){
    set_running.continous = (uint8_t)status;
    return;
}

//nastavení samplerate
void DMM_SRate(uint16_t SR){
    if(HW_SR((uint16_t)SR)){
        
    }else{
    set_running.sampleRate =(uint16_t) SR;
    }
    return;
}

//vrátí zda je zařízení v continous
uint8_t DMM_modeContinous()
{
    return set_running.continous;
}

//*------------------------------------------*/
/*      Neblokující vzorkování               */
/*-------------------------------------------*/

uint8_t DMM_Asyncsample(uint8_t channel){
    float tmp;
    tmp = HW_async_get();
    if(tmp!=FLT_MIN){
        data_last[channel%2][channel/2] = tmp;
        //hledá další aktivní kanál (pokud nenajde zůstane na stejném)
        uint8_t channel_tmp = channel + 1;
        channel_tmp = channel_tmp % 4;
        while(set_running.activeChannels[channel_tmp]==0){
            channel ++;
            channel = channel%4;
            if(channel_tmp == channel){
                break;
            }
        }
        channel = channel_tmp;
        if(channel%2){
            HW_async_current_start(channel/2);
        }else{
            HW_async_volt_start(channel/2);
        }
        return (channel);
    }
    return channel;
}
