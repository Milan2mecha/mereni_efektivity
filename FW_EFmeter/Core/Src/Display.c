#include "ssd1306.h"
#include "fonts.h"
#include <string.h>



void DP_init(void){
SSD1306_Init();
SSD1306_Clear();
SSD1306_UpdateScreen();
}
uint8_t transform(float in)
{
    char str[7] = {0};
    if(in<0){
        strcpy(str,"-");
        in *= -1;
    }
    if (in<0.1){ 
        in *= 1000;
    }
        int16_t tmp = (int16_t)in;
        itoa(tmp,&str[strlen(str)],10);
        strcat(str,",");
        tmp = (int16_t)((in-(uint16_t)in)*1000);
        if (tmp<100)
        {
            strcat(str,"0");
        }
        if (tmp<10)
        {
            strcat(str,"0");
        }       
        itoa(tmp,&str[strlen(str)],10);
        SSD1306_Puts(str, &Font_11x18, 1);
        return strlen(str);
}
void DrawPage1(float row1, float row2){
    SSD1306_Clear();
    //row1
    SSD1306_GotoXY (5,3);
    SSD1306_Puts("U1=", &Font_11x18, 1);
    SSD1306_GotoXY (38,3);
    uint8_t move = transform(row1);
    SSD1306_GotoXY(38+(11*move),3);
    if(row1<0.1){
        SSD1306_Putc('m',&Font_11x18, 1);
    }
    //row2
    SSD1306_GotoXY (5,25);
    SSD1306_Puts("I1=", &Font_11x18, 1);
    SSD1306_GotoXY (38,25);
    move = transform(row2);
    SSD1306_GotoXY(38+(11*move),25);
    if(row2<0.1){
        SSD1306_Putc('m',&Font_11x18, 1);
    }
    SSD1306_UpdateScreen();
}
void DrawSCPI()
{
    SSD1306_Clear();
    SSD1306_GotoXY (10,21);
    SSD1306_Puts("USB-SCPI", &Font_11x18, 1);
    SSD1306_UpdateScreen();
}
void DrawERR(int16_t error)
{
    char str[7] = {0};
    SSD1306_Clear();
    SSD1306_GotoXY (10,3);
    SSD1306_Puts("Error:", &Font_11x18, 1);
    SSD1306_GotoXY (10,25);
    itoa(error,&str[strlen(str)],10);
    SSD1306_Puts(str, &Font_11x18, 1);
    SSD1306_UpdateScreen();
}