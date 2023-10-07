/*
    Single-shot conversion using Interrupt
*/

#include <ez8.h>
#include <sio.h>
#include <stdio.h>

void initADC(void);
void delay_ms(unsigned int delay);

#pragma interrupt

void isrADC(void) {
    unsigned int value;
    value = ((ADLR >> 6) | (ADHR << 2));
    printf("ADC: %4.2f Volts and 0x%03X\n", value / 512.0, value);
}

void main() {
    initADC();
    init_uart(_UART1, _DEFFREQ, 9600);
    select_port(_UART1);
    while(1) {
        ACTL |= 0x80;
        delay_ms(1000);
    }
}

void initADC(void) {
    PBAF |= 0x01;
    ACTL = 0x00;
    DI();
    SET_VECTOR(ADC, isrADC);
    IRQ0ENH = 0x01;
    IRQ0ENL = 0x01;
    IRQ0 &= ~0x01;
    EI();
}

void delay_ms(unsigned int delay) {
    unsigned int x, y;
    for(x = 0; x <= delay; x++)
        for(y = 0; y <= 512; y++);
}