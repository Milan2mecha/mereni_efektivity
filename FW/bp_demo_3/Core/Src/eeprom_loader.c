#include "eeprom.h"
extern uint16_t VirtAddVarTab[NB_OF_VAR];

typedef union {
    uint16_t eeprom[4];
    double out;
    
 }Data;

void save_to_eeprom(uint16_t pos, double data){
    Data tmp;
    tmp.out = data;
    for(uint8_t i=0; i<4;i++){
    EE_WriteVariable(VirtAddVarTab[pos+i],tmp.eeprom[i]);
    }
}
double read_form_eeprom(uint16_t pos){
    Data tmp;
    for(uint8_t i=0; i<4;i++){
        EE_ReadVariable(VirtAddVarTab[pos+i], &tmp.eeprom[i]);
    }
    return tmp.out;
}