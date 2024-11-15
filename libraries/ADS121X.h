

//#ifndef ADS121X_addr
#define ADS121X_addr    0x40
#define AIN0 0
#define AIN1 1
#define AIN2 2 
#define AIN3 3
#define AGND 4
#define calibration 5

void ADS121X_init(void);
uint8_t ADS121X_VREF(uint8_t);
uint8_t ADS121X_RREG(uint8_t);
uint8_t ADS121X_MUX(uint8_t, uint8_t);
uint8_t ADS121X_CM(uint8_t);
void ADS121X_cal(void);
uint16_t ADS121X_DR(uint16_t);
void ADS121X_POWERDOWN(void);

int32_t ADS121X_measure(void);
int32_t ADS121X_measure_sg(void);
