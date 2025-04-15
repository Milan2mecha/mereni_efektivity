#include <stdlib.h>
#include <string.h>
#include "scpi/scpi.h"
#include "scpi-proto.h"
#include "DMM.h"
#include "eeprom_loader.h"
#include "HW_hand.h"

/*----------------------------------------------*/
/*                  SYSMODE                      */
/*----------------------------------------------*/

//list módů
static scpi_choice_def_t mode_list[] = {
    {"OFF", 0},
    {"DMM", 1},
    {"BTES", 2},
    SCPI_CHOICE_LIST_END /* termination of option list */
};

//sysmode
scpi_result_t SYS_MODE(scpi_t * context){
    int32_t param;
    if (!SCPI_ParamChoice(context, mode_list, &param, TRUE)) {
        return SCPI_RES_ERR;
    }
    switch (param)
    {
    case 1:
            if(DMM_Enable()!=1){
            SCPI_ErrorPush(context, -200);
            return SCPI_RES_ERR;
        }
        break;
    
    default:
            if(DMM_Disable()!=1){
            SCPI_ErrorPush(context, -200);
            return SCPI_RES_ERR;
        }
        break;
    }

    return SCPI_RES_OK;                                      
}

//sysmode?
scpi_result_t SYS_MODEQ(scpi_t * context){
    DMM_set tmp_DMM  = DMM_Status();
    if(tmp_DMM.status){
        SCPI_ResultMnemonic(context, "DMM");
    }else if(0){
        SCPI_ResultMnemonic(context, "BTES");
    } else
    {
        SCPI_ResultMnemonic(context, "OFF");
    }
    return SCPI_RES_OK;                                         
}

/*----------------------------------------------*/
/*                MEASURE subsystem             */
/*----------------------------------------------*/
//Napětí
scpi_result_t DMM_MeasureVoltageDcQ(scpi_t * context) {
    int32_t channel;
    SCPI_CommandNumbers(context, &channel, 1,0);
    if((channel != 1 )&&(channel != 2)){
        SCPI_ErrorPush(context, -224);
        return SCPI_RES_ERR;
    }
    DMM_out out = DMM_Voltage((uint8_t)channel-1);
    if(out.status != 1){
        SCPI_ErrorPush(context, -200);
        return SCPI_RES_ERR;
    }
    if(out.error != 0){
        SCPI_ErrorPush(context, -200);
        return SCPI_RES_ERR;
    }
    SCPI_ResultDouble(context, out.result);

    return SCPI_RES_OK;
}
//Proud
scpi_result_t DMM_MeasureCurrentDcQ(scpi_t * context) {
    int32_t channel;
    SCPI_CommandNumbers(context, &channel, 1,0);
    if((channel != 1 )&&(channel != 2)){
        SCPI_ErrorPush(context, -224);
        return SCPI_RES_ERR;
    }
    DMM_out out = DMM_Current((uint8_t)channel-1);
    if(out.status != 1){
        SCPI_ErrorPush(context, -200);
        return SCPI_RES_ERR;
    }
    if(out.error != 0){
        SCPI_ErrorPush(context, -200);
        return SCPI_RES_ERR;
    }
    SCPI_ResultDouble(context, out.result);
    return SCPI_RES_OK;
}
//Výkon
scpi_result_t DMM_MeasurePowerQ(scpi_t * context){
    int32_t channel;
    SCPI_CommandNumbers(context, &channel, 1,0);
    if((channel != 1 )&&(channel != 2)){
        SCPI_ErrorPush(context, -224);
        return SCPI_RES_ERR;
    }
    DMM_out out = DMM_Power((uint8_t)channel-1);
    if(out.status != 1){
        SCPI_ErrorPush(context, -200);
        return SCPI_RES_ERR;
    }
    if(out.error != 0){
        SCPI_ErrorPush(context, -200);
        return SCPI_RES_ERR;
    }
    SCPI_ResultDouble(context, out.result);
    return SCPI_RES_OK;
}


/*----------------------------------------------*/
/*                FETCH subsystem             */
/*----------------------------------------------*/
//fetch current
scpi_result_t DMM_FetchCurrentQ(scpi_t * context){
    int32_t channel;
    SCPI_CommandNumbers(context, &channel, 1,0);
    if((channel != 1 )&&(channel != 2)){
        SCPI_ErrorPush(context, -224);
        return SCPI_RES_ERR;
    }
    DMM_out out = DMM_Fetch_current((uint8_t)channel);
    if(out.status != 1){
        SCPI_ErrorPush(context, -200);
        return SCPI_RES_ERR;
    }
    if(out.error != 0){
        SCPI_ErrorPush(context, -200);
        return SCPI_RES_ERR;
    }
    SCPI_ResultDouble(context, out.result);
    return SCPI_RES_OK;
}

scpi_result_t DMM_FetchVoltageQ(scpi_t * context){
    int32_t channel;
    SCPI_CommandNumbers(context, &channel, 1,0);
    if((channel != 1 )&&(channel != 2)){
        SCPI_ErrorPush(context, -224);
        return SCPI_RES_ERR;
    }
    DMM_out out = DMM_Fetch_volt((uint8_t)channel);
    if(out.status != 1){
        SCPI_ErrorPush(context, -200);
        return SCPI_RES_ERR;
    }
    if(out.error != 0){
        SCPI_ErrorPush(context, -200);
        return SCPI_RES_ERR;
    }
    SCPI_ResultDouble(context, out.result);
    return SCPI_RES_OK;
}

/*------------------------------------------------------*/
/*              Configurace měření                      */
/*------------------------------------------------------*/

//sample rate
scpi_result_t DMM_ConfigureSR(scpi_t * context){
    int32_t param;
    SCPI_ParamInt32(context, &param, TRUE);
    if((param != 20 )&&(param != 90)&&(param != 330)&&(param != 1000)){
        SCPI_ErrorPush(context, -224);
        return SCPI_RES_ERR;
    }
    DMM_SRate((uint16_t)param);
    return SCPI_RES_OK;
}

//sample rate?
scpi_result_t DMM_SRATeQ(scpi_t * context){
    DMM_set tmp  = DMM_Status();
    SCPI_ResultInt32(context, tmp.sampleRate);
    return SCPI_RES_OK;
}

//continous
scpi_result_t DMM_CONTinous(scpi_t * context){
    int32_t param;
    if (!SCPI_ParamInt32(context, &param, TRUE)) {
        return SCPI_RES_ERR;
    }
    DMM_Continous(param);
    return SCPI_RES_OK;
}

//continous?
scpi_result_t DMM_ContinousQ(scpi_t * context){
    int32_t param;
    SCPI_ParamInt32(context, &param, TRUE);
    return SCPI_RES_OK;
}



/*----------------------------------------------------------*/
/*              Vkládání do eeprom                          */
/*----------------------------------------------------------*/
//Vstupní proud
scpi_result_t CAL_Icur(scpi_t * context){
    int32_t range;
    SCPI_CommandNumbers(context, &range, 1,0);
    if((range!=1)&&(range!=5)){
        return SCPI_RES_ERR;
    }
    double param1, param2, param3;
    if (!SCPI_ParamDouble(context, &param1, TRUE)) {
        return SCPI_RES_ERR;
    }
    if (!SCPI_ParamDouble(context, &param2, TRUE)) {
        return SCPI_RES_ERR;
    }
    if (!SCPI_ParamDouble(context, &param3, TRUE)) {
        return SCPI_RES_ERR;
    }
    if(range == 1){
        param_to_eeprom(I21_ee, param1, param2, param3);
    }else{
        param_to_eeprom(I22_ee, param1, param2, param3);
    }
    
    load_EEPROM();
    return SCPI_RES_OK;
}
//Výstupní proud
scpi_result_t CAL_Ocur(scpi_t * context){
    int32_t range;
    SCPI_CommandNumbers(context, &range, 1,0);
    if((range!=1)&&(range!=5)){
        return SCPI_RES_ERR;
    }
    double param1, param2, param3;
    if (!SCPI_ParamDouble(context, &param1, TRUE)) {
        return SCPI_RES_ERR;
    }
    if (!SCPI_ParamDouble(context, &param2, TRUE)) {
        return SCPI_RES_ERR;
    }
    if (!SCPI_ParamDouble(context, &param3, TRUE)) {
        return SCPI_RES_ERR;
    }
    if(range == 1){
        param_to_eeprom(I11_ee, param1, param2, param3);
    }else{
        param_to_eeprom(I12_ee, param1, param2, param3);
    }  
    load_EEPROM();
    return SCPI_RES_OK;
//Vstupní napětí
}scpi_result_t CAL_Ivol(scpi_t * context){
    double param1, param2, param3;
    if (!SCPI_ParamDouble(context, &param1, TRUE)) {
        return SCPI_RES_ERR;
    }
    if (!SCPI_ParamDouble(context, &param2, TRUE)) {
        return SCPI_RES_ERR;
    }
    if (!SCPI_ParamDouble(context, &param3, TRUE)) {
        return SCPI_RES_ERR;
    }
    param_to_eeprom(U2_ee, param1, param2, param3);
    load_EEPROM();
    return SCPI_RES_OK;
}
//Výstupní napětí
scpi_result_t CAL_Ovol(scpi_t * context){
    double param1, param2, param3;
    if (!SCPI_ParamDouble(context, &param1, TRUE)) {
        return SCPI_RES_ERR;
    }
    if (!SCPI_ParamDouble(context, &param2, TRUE)) {
        return SCPI_RES_ERR;
    }
    if (!SCPI_ParamDouble(context, &param3, TRUE)) {
        return SCPI_RES_ERR;
    }
    param_to_eeprom(U1_ee, param1, param2, param3);
    load_EEPROM();
    return SCPI_RES_OK;
}