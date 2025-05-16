#include "eeprom.h"
extern uint16_t VirtAddVarTab[NB_OF_VAR];

//Převod dat na double
typedef union {
    uint16_t eeprom[4];
    double out;
 }Data;

//Uložení jednoho doublu
void save_to_eeprom(uint16_t pos, double data){
    Data tmp;
    tmp.out = data;
    for(uint8_t i=0; i<4;i++){
    EE_WriteVariable(VirtAddVarTab[pos+i],tmp.eeprom[i]);
    }
}
//Přečtení jednoho doublu
double read_form_eeprom(uint16_t pos){
    Data tmp;
    for(uint8_t i=0; i<4;i++){
        EE_ReadVariable(VirtAddVarTab[pos+i], &tmp.eeprom[i]);
    }
    return tmp.out;
}
//Hromadné uložení
void param_to_eeprom(uint16_t pos, double data1, double data2, double data3){
    save_to_eeprom(pos, data1);
    save_to_eeprom(pos+4, data2);
    save_to_eeprom(pos+8, data3);
}
