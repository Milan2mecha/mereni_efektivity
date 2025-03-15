
#include "scpi/scpi.h"

scpi_result_t SYS_MODEQ(scpi_t * context);
scpi_result_t SYS_MODE(scpi_t * context);

scpi_result_t DMM_MeasureVoltageDcQ(scpi_t * context);
scpi_result_t DMM_MeasurePowerQ(scpi_t * context);
scpi_result_t DMM_MeasureCurrentDcQ(scpi_t * context);
scpi_result_t DMM_ConfigureSR(scpi_t * context);
scpi_result_t DMM_Continous(scpi_t * context);
scpi_result_t DMM_ConfigureQ(scpi_t * context);
scpi_result_t DMM_FetchCurrentQ(scpi_t * context);
scpi_result_t DMM_FetchVoltageQ(scpi_t * context);