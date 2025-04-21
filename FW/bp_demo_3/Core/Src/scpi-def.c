/*-
 * BSD 2-Clause License
 *
 * Copyright (c) 2012-2018, Jan Breuer
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file   scpi-def.c
 * @date   Thu Nov 15 10:58:45 UTC 2012
 *
 * @brief  SCPI parser test
 *
 *
 */
#include <stdio.h>
#include "scpi/scpi.h"
#include "scpi-def.h"
#include "scpi-proto.h"
#include "usb_device.h"
#include "Display.h"


/**
 * Reimplement IEEE488.2 *TST?
 *
 * Result should be 0 if everything is ok
 * Result should be 1 if something goes wrong
 *
 * Return SCPI_RES_OK
 */
	size_t SCPI_Write(scpi_t * context, const char * data, size_t len) {
	    (void) context;
	    while (CDC_Transmit_FS(data, len));
	    return SCPI_RES_OK;
	}

	scpi_result_t SCPI_Flush(scpi_t * context) {
	    (void) context;
	    return SCPI_RES_OK;
	}

	int SCPI_Error(scpi_t * context, int_fast16_t err) {
	    (void) context;
	    char errs[50];
	    sprintf(errs, "**ERROR: %d, \"%s\"\r\n", (int16_t) err, SCPI_ErrorTranslate(err));
	    CDC_Transmit_FS(errs, strlen(errs)+1);
        DrawERR((uint16_t)err);
        
	    return 0;
	}

	scpi_result_t SCPI_Control(scpi_t * context, scpi_ctrl_name_t ctrl, scpi_reg_val_t val) {
	    (void) context;
	    char errs[50];
	    if (SCPI_CTRL_SRQ == ctrl) {
	    	sprintf(errs, "**SRQ: 0x%X (%d)\r\n", val, val);
	    } else {
	    	sprintf(errs, "**CTRL %02x: 0x%X (%d)\r\n", ctrl, val, val);
	    }
	    CDC_Transmit_FS(errs, strlen(errs)+1);
	    return SCPI_RES_OK;
	}

	scpi_result_t SCPI_Reset(scpi_t * context) {
	    (void) context;
	    char errs[50];
	    sprintf(errs, "**Reset\r\n");
	    CDC_Transmit_FS(errs, strlen(errs)+1);

	    return SCPI_RES_OK;
	}


static scpi_result_t My_CoreTstQ(scpi_t * context) {

    SCPI_ResultInt32(context, 0);

    return SCPI_RES_OK;
}

const scpi_command_t scpi_commands[] = {
    /* IEEE Mandated Commands (SCPI std V1999.0 4.1.1) */
    { .pattern = "*CLS", .callback = SCPI_CoreCls,},
    { .pattern = "*ESE", .callback = SCPI_CoreEse,},
    { .pattern = "*ESE?", .callback = SCPI_CoreEseQ,},
    { .pattern = "*ESR?", .callback = SCPI_CoreEsrQ,},
    { .pattern = "*IDN?", .callback = SCPI_CoreIdnQ,},
    { .pattern = "*OPC", .callback = SCPI_CoreOpc,},
    { .pattern = "*OPC?", .callback = SCPI_CoreOpcQ,},
    { .pattern = "*RST", .callback = SCPI_CoreRst,},
    { .pattern = "*SRE", .callback = SCPI_CoreSre,},
    { .pattern = "*SRE?", .callback = SCPI_CoreSreQ,},
    { .pattern = "*STB?", .callback = SCPI_CoreStbQ,},
    { .pattern = "*TST?", .callback = My_CoreTstQ,},
    { .pattern = "*WAI", .callback = SCPI_CoreWai,},

    /* Required SCPI commands (SCPI std V1999.0 4.2.1) */
    {.pattern = "SYSTem:ERRor[:NEXT]?", .callback = SCPI_SystemErrorNextQ,},
    {.pattern = "SYSTem:ERRor:COUNt?", .callback = SCPI_SystemErrorCountQ,},
    {.pattern = "SYSTem:VERSion?", .callback = SCPI_SystemVersionQ,},



    {.pattern = "STATus:QUEStionable[:EVENt]?", .callback = SCPI_StatusQuestionableEventQ,},
    /* {.pattern = "STATus:QUEStionable:CONDition?", .callback = scpi_stub_callback,}, */
    {.pattern = "STATus:QUEStionable:ENABle", .callback = SCPI_StatusQuestionableEnable,},
    {.pattern = "STATus:QUEStionable:ENABle?", .callback = SCPI_StatusQuestionableEnableQ,},
    {.pattern = "STATus:PRESet", .callback = SCPI_StatusPreset,},

    {.pattern = "SYStem:MODE?", .callback = SYS_MODEQ,},
    {.pattern = "SYStem:MODE", .callback = SYS_MODE,},
    {.pattern = "BTESt:CHANnel", .callback = BTES_MODE,},
    /* DMM */
    {.pattern = "MEASure:VOLTage#?", .callback = DMM_MeasureVoltageDcQ,},
    {.pattern = "MEASure:CURRent#?", .callback = DMM_MeasureCurrentDcQ,},
    {.pattern = "MEASure:POWer#?", .callback = DMM_MeasurePowerQ,},
    {.pattern = "SENSe:SRATe",.callback = DMM_ConfigureSR,},
    {.pattern = "SENSe:CONTinous",.callback = DMM_CONTinous,},
    {.pattern = "FETCh:VOLTage#?",.callback = DMM_FetchVoltageQ,},
    {.pattern = "FETCh:CURRent#?",.callback = DMM_FetchCurrentQ,},
    {.pattern = "SENSe:SRATe?",.callback = DMM_SRATeQ,},

    /*kalibrace*/
    {.pattern = "CALibrate:ICURrent#",.callback = CAL_Icur,},
    {.pattern = "CALibrate:OCURrent#",.callback = CAL_Ocur,},
    {.pattern = "CALibrate:IVOLtage",.callback = CAL_Ivol,},
    {.pattern = "CALibrate:OVOLtage",.callback = CAL_Ovol,},
    {.pattern = "CALibrate:ICURrent#?",.callback = CAL_IcurQ,},
    {.pattern = "CALibrate:OCURrent#?",.callback = CAL_OcurQ,},
    {.pattern = "CALibrate:IVOLtage?",.callback = CAL_IvolQ,},
    {.pattern = "CALibrate:OVOLtage?",.callback = CAL_OvolQ,},
    SCPI_CMD_LIST_END
    };

char scpi_input_buffer[SCPI_INPUT_BUFFER_LENGTH];
scpi_error_t scpi_error_queue_data[SCPI_ERROR_QUEUE_SIZE];


scpi_interface_t scpi_interface = {
    .error = SCPI_Error,
    .write = SCPI_Write,
    .control = SCPI_Control,
    .flush = SCPI_Flush,
    .reset = SCPI_Reset,
};

scpi_t scpi_context;
