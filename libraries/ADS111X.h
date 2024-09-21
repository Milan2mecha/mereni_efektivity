

//#ifndef ADS111X_addr
#define ADS111X_addr    0b10000000
#define AIN0 0
#define AIN1 1
#define AIN2 2 
#define AIN3 3
#define AGND 4
#define calibration 5

void ADS111X_init(void);
uint16_t ADS111X_read(void);
uint8_t ADS111X_RREG(uint8_t);
uint8_t ADS111X_MUX(uint8_t, uint8_t);
void ADS111X_cal(void);
uint16_t ADS111X_DR(uint16_t);
