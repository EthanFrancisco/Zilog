#include <ez8.h>
#include <sio.h>
#include <stdio.h>

#define NObj 650
#define WObj 650

void initAdcR(void);
void initAdcF(void);
void initAdcL(void);
void delay_ms(unsigned int delay);
unsigned int ADCout(void);

void main() {
    unsigned int DVR, DVF, DVL;
    init_uart(_UART0, _DEFFREQ, 9600);
    select_port(_UART0);
    while(1) {
        initAdcR(); DVR = ADCout();
        initAdcF(); DVF = ADCout();
        initAdcL(); DVL = ADCout();
        printf("R = %4d F = %4d L = %4d\r", DVR, DVF, DVL);
        if((DVR < NObj) && (DVF >= WObj) && (DVL < NObj)) {
            printf("Attack!!!!!\r");
        } else if((DVR >= WObj) && (DVF < NObj) && (DVL < NObj)) {
            printf("Turn Right\r");
        } else if((DVR < NObj) && (DVF < NObj) && (DVL >= WObj)) {
            printf("Turn Left\r");
        } else
            printf("Searching......\r");
        delay_ms(200);
    }
}

void initAdcR(void) {
    PBAF |= 0x01;
    ACTL = 0x00;
}

void initAdcF(void) {
    PBAF |= 0x02;
    ACTL = 0x01;
}

void initAdcL(void) {
    PBAF |= 0x04;
    ACTL = 0x02;
}

unsigned int ADCout(void) {
    unsigned int value;
    ACTL |= 0x80;
    while(ACTL & 0x80);
    value = ((ADLR >> 6) | (ADHR << 2));
    return value;
}

void delay_ms(unsigned int delay) {
    unsigned int x, y;
    for(x = 0; x <= delay; x++)
        for(y = 0; y <= 512; y++);
}