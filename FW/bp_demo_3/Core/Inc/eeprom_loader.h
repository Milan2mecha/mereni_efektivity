#define U1_ee 0
#define U2_ee 72
#define I11_ee 24
#define I12_ee 48
#define I21_ee 96
#define I22_ee 120

void save_to_eeprom(uint16_t pos, double data);
float read_form_eeprom(uint16_t pos);
void param_to_eeprom(uint16_t pos, double data1, double data2, double data3);