
#include "scpi/scpi.h"

scpi_result_t SYS_MODEQ(scpi_t * context);
scpi_result_t SYS_MODE(scpi_t * context);
scpi_result_t BTES_MODE(scpi_t * context);

scpi_result_t DMM_MeasureVoltageDcQ(scpi_t * context);
scpi_result_t DMM_MeasurePowerQ(scpi_t * context);
scpi_result_t DMM_MeasureCurrentDcQ(scpi_t * context);
scpi_result_t DMM_ConfigureSR(scpi_t * context);
scpi_result_t DMM_CONTinous(scpi_t * context);
scpi_result_t DMM_ContinousQ(scpi_t * context);
scpi_result_t DMM_FetchCurrentQ(scpi_t * context);
scpi_result_t DMM_FetchVoltageQ(scpi_t * context);
scpi_result_t DMM_SRATeQ(scpi_t * context);
scpi_result_t CAL_Ovol(scpi_t * context);
scpi_result_t CAL_Ivol(scpi_t * context);
scpi_result_t CAL_Ocur(scpi_t * context);
scpi_result_t CAL_Icur(scpi_t * context);
scpi_result_t CAL_OvolQ(scpi_t * context);
scpi_result_t CAL_IvolQ(scpi_t * context);
scpi_result_t CAL_OcurQ(scpi_t * context);
scpi_result_t CAL_IcurQ(scpi_t * context);