#include <stdlib.h>
#include <string.h>
#include "scpi/scpi.h"
#include "scpi-proto.h"
#include "DMM.h"

/*----------------------------------------------*/
/*                  SYS - prototypes            */
/*----------------------------------------------*/

static scpi_choice_def_t mode_list[] = {
    {"OFF", 0},
    {"DMM", 1},
    {"BTES", 2},
    SCPI_CHOICE_LIST_END /* termination of option list */
};

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
scpi_result_t SYS_MODEQ(scpi_t * context){
    if(DMM_status){
        SCPI_ResultMnemonic(context, "DMM");
    }else if(DMM_status){
        SCPI_ResultMnemonic(context, "BTES");
    } else
    {
        SCPI_ResultMnemonic(context, "OFF");
    }
    return SCPI_RES_OK;                                         
}

/*----------------------------------------------*/
/*                  DMM - prototypes            */
/*----------------------------------------------*/
scpi_result_t DMM_MeasureVoltageDcQ(scpi_t * context) {
    	int32_t param;
    	SCPI_ParamInt32(context, &param, TRUE);
        if((param != 1 )&&(param != 2)){
        SCPI_ErrorPush(context, 2);
        return SCPI_RES_ERR;
        }
        if(DMM_status != 1){
        SCPI_ErrorPush(context, 1);
        return SCPI_RES_ERR;
        }
    double out = DMM_voltage((uint8_t)param);
    SCPI_ResultFloat(context, out);

    return SCPI_RES_OK;
}
scpi_result_t DMM_MeasureCurrentDcQ(scpi_t * context) {
    int32_t param;
    SCPI_ParamInt32(context, &param, TRUE);
    if((param != 1 )&&(param != 2)){
        SCPI_ErrorPush(context, -200);
        return SCPI_RES_ERR;
    }
    if(DMM_status != 1){
        SCPI_ErrorPush(context, 1);
        return SCPI_RES_ERR;
    }

    double out = DMM_current((uint8_t)param);
    SCPI_ResultDouble(context, out);

    return SCPI_RES_OK;
}

scpi_result_t DMM_MeasurePowerQ(scpi_t * context){
    int32_t param;
    SCPI_ParamInt32(context, &param, TRUE);
    if((param != 1 )&&(param != 2)){
        SCPI_ErrorPush(context, -200);
        return SCPI_RES_ERR;
    }
    if(DMM_status != 1){
        SCPI_ErrorPush(context, -200);
        return SCPI_RES_ERR;
    }

    double out = DMM_power((uint8_t)param);

    SCPI_ResultDouble(context, out);
    return SCPI_RES_OK;
}

/*scpi_result_t DMM_MeasureEfectivityQ(scpi_t *context){
    if(DMM_status != 1){
        SCPI_ErrorPush(context, 1);
        return SCPI_RES_ERR;
    }
    double out = DMM_power(1);
    SCPI_ResultDouble(context, out);
    return SCPI_RES_OK;
}*/

