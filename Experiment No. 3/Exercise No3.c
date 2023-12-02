#include <ez8.h>
#include <sio.h>
#include <stdio.h>

#define CHANNEL 0x00
#define MODE    0x10
#define VREF    0x00
#define ENABLE  0x80

#define waterThreshold 512  // Adjustable per water immersion of the level sensor

void initADC(void);
void delay_ms(unsigned int delay);
unsigned int PollADC1(void);
unsigned int PollADCn(void);

void main() {
    unsigned int dValue = 0;
    PAAF |= 0x30;
    init_uart(_UART0, _DEFFREQ, _DEFBAUD);
    select_port(_UART0);
    initADC();
    dValue = PollADC1();
    while(1) {
        dValue = PollADCn();
        printf("Digital Value of Level: 0x%03X\r", dValue);
        if(dValue >= waterThreshold) {
            printf("Water level is above the alarming threshold! Consider evacuating!\n");
        } else {
            printf("Water level is below the threshold!\n");
        }
        delay_ms(100);
    }
}

void initADC(void) {
    PBAF |= 0x01;
    ACTL = (CHANNEL | MODE | VREF);
}

unsigned int PollADC1(void) {
    ACTL |= ENABLE;
    while(ACTL&ENABLE);
    return(((unsigned int) ADHR << 2) | (ADLR >> 6));
}

unsigned int PollADCn(void) {
    return(((unsigned int) ADHR << 2) | (ADLR >> 6));
}

void delay_ms(unsigned int delay) {
    unsigned int x, y;
    for(x = 0; x <= delay; x++)
        for(y = 0; y <= 512; y++);
}