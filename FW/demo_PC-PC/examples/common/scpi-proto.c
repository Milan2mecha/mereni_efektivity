#include <stdlib.h>
#include <string.h>
#include "scpi/scpi.h"
#include "scpi-proto.h"
#include "dev/DMM.h"

/*----------------------------------------------*/
/*                  SYS - prototypes            */
/*----------------------------------------------*/

static scpi_choice_def_t mode_list[] = {
    {"DMM", 1},
    {"CAL", 2},
    SCPI_CHOICE_LIST_END /* termination of option list */
};

scpi_result_t SYS_MODE(scpi_t * context){
    int32_t param;
    if (!SCPI_ParamChoice(context, mode_list, &param, TRUE)) {
        return SCPI_RES_ERR;
    }
    if (param == 1)
    {
        if(DMM_Enable()!=1){
            SCPI_ErrorPush(context, 3);
            return SCPI_RES_ERR;
        }
    }
    return SCPI_RES_OK;                                      
}
scpi_result_t SYS_MODEQ(scpi_t * context){
    if(DMM_status){
        SCPI_ResultMnemonic(context, "DMM");
    }
    return SCPI_RES_OK;                                         
}

/*----------------------------------------------*/
/*                  DMM - prototypes            */
/*----------------------------------------------*/
scpi_result_t DMM_MeasureVoltageDcQ(scpi_t * context) {
    double param;

    if (!SCPI_ParamDouble(context, &param, TRUE)) {
        /* do something, if parameter not present */
    }
        if((param != 1 )&&(param != 2)){
        SCPI_ErrorPush(context, 2);
        return SCPI_RES_ERR;
    }
        if(DMM_status != 1){
        SCPI_ErrorPush(context, 1);
        return SCPI_RES_ERR;
    }
    double out = DMM_voltage((uint8_t)param);
    SCPI_ResultDouble(context, out);
    return SCPI_RES_OK;
}
scpi_result_t DMM_MeasureCurrentDcQ(scpi_t * context) {
    double param;
    SCPI_ParamDouble(context, &param, TRUE);
    if((param != 1 )&&(param != 2)){
        SCPI_ErrorPush(context, 2);
        return SCPI_RES_ERR;
    }
    if(DMM_status != 1){
        SCPI_ErrorPush(context, 1);
        return SCPI_RES_ERR;
    }

    double out = DMM_voltage((uint8_t)param);
    SCPI_ResultDouble(context, out);

    return SCPI_RES_OK;
}

scpi_result_t DMM_MeasurePowerQ(scpi_t * context){
    double param;
    SCPI_ParamDouble(context, &param, TRUE);
    if((param != 1 )&&(param != 2)){
        SCPI_ErrorPush(context, 2);
        return SCPI_RES_ERR;
    }
    if(DMM_status != 1){
        SCPI_ErrorPush(context, 1);
        return SCPI_RES_ERR;
    }

    double out = DMM_power((uint8_t)param);

    SCPI_ResultDouble(context, out);
    return SCPI_RES_OK;
}

scpi_result_t DMM_MeasureEfectivityQ(scpi_t *context){
    if(DMM_status != 1){
        SCPI_ErrorPush(context, 1);
        return SCPI_RES_ERR;
    }
    double out = DMM_efectivity();
    SCPI_ResultDouble(context, out);
    return SCPI_RES_OK;
}

