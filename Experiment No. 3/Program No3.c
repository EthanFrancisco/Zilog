#include <ez8.h>
#include <sio.h>
#include <stdio.h>

#define CHANNEL 0x03
#define MODE    0x10
#define VREF    0x00
#define ENABLE  0x80

void init_ADC(void);
void delay_ms(unsigned int delay);
unsigned int analogRead1(void);
unsigned int analogReadn(void);

void main() {
    unsigned int dValue = 0;

    PAAF |= 0x30;

    init_uart(_UART0, _DEFFREQ, _DEFBAUD);
    select_port(_UART0);
    init_ADC();
    dValue = analogRead1();
    printf("0x%03X\n", dValue);
    while(1) {
        delay(100);
        dValue = analogReadn();
        printf("0x%03X\r", dValue);
    }
}

void init_ADC(void) {
    PBAF |= 0x08;
    ACTL = (CHANNEL | MODE | VREF);
}

unsigned int analogRead1(void) {
    ACTL |= ENABLE;
    while(ACTL&ENABLE);
    return(((unsigned int) ADHR << 2) | (ADLR >> 6));
}

unsigned int analogReadn(void) {
    return(((unsigned int) ADHR << 2) | (ADLR >> 6));
}

void delay_ms(unsigned int delay) {
    unsigned int x, y;
    for(x = 0; x <= delay; x++)
        for(y = 0; y <= 512; y++);
}