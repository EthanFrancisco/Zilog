/*
    Multiple channels (combined single-shot and continuous modes)
*/

#include <ez8.h>
#include <sio.h>
#include <stdio.h>

#define CHANNEL3    0x03
#define CHANNEL2    0x02
#define CHANNEL1    0x01
#define CHANNEL0    0x00
#define MODE1   0x00
#define MODEC   0x10
#define VREF    0x00
#define ENABLE  0x80

void Init_ADC3(void);
void Init_ADC2(void);
void Init_ADC1(void);
void Init_ADC0(void);
unsigned int PollADC(void);
void delay_ms(unsigned int delay);

void main() {
    unsigned int VALUE = 0;
    float volts = 0.0;
    unsigned char DATA;

    init_uart(_UART0, _DEFFREQ, _DEFBAUD);
    select_port(_UART0);
    while(1) {
        DATA = getch();
        if(DATA == 'A') {
            Init_ADC3();
            VALUE = PollADC();
            volts = VALUE / 512.0;
            printf("ADC3: 0x%X, %8.3f volts\n", VALUE, volts);
        } else if(DATA == 'D') {
            Init_ADC2();
            VALUE = PollADC();
            volts = VALUE / 512.0;
            printf("ADC2: 0x%X, %8.3f volts\n", VALUE, volts);
        } else if(DATA == 'W') {
            Init_ADC1();
            VALUE = PollADC();
            volts = VALUE / 512.0;
            printf("ADC1: 0x%X, %8.3f volts\n", VALUE, volts);
        } else if(DATA == 'S') {
            Init_ADC();
            VALUE = PollADC();
            volts = VALUE / 512.0;
            printf("ADC0: 0x%X, %8.3f volts\n", VALUE, volts);
        }
    }
}

void Init_ADC3(void) {
    PBAF |= 0x08;
    ACTL = (CHANNEL3 | MODEC | VREF);
}

void Init_ADC2(void) {
    PBAF |= 0x04;
    ACTL = (CHANNEL2 | MODE1 | VREF);
}

void Init_ADC1(void) {
    PBAF |= 0x02;
    ACTL = (CHANNEL1 | MODE1 | VREF);
}

void Init_ADC0(void) {
    PBAF |= 0x01;
    ACTL = (CHANNEL0 | MODE1 | VREF);
}

unsigned int PollADC(void) {
    ACTL |= ENABLE;
    while(ACTL&ENABLE);
    return(((unsigned int) ADHR << 2) | (ADLR >> 6));
}

void delay_ms(unsigned int delay) {
    unsigned int x, y;
    for(x = 0; x <= delay; x++)
        for(y = 0; y <= 512; y++);
}