#include <ez8.h>
#include <sio.h>
#include <stdio.h>

char Letter;

void delay_ms(unsigned int delay);
void Init_UART1(void);
void Clear_Message(void);

void main() {
    PADD = 0x00;
    PAAF = 0x00;
    PAOC = 0x00;
    PAHDE = 0xFF;

    init_uart(_UART1, _DEFFREQ, _DEFBAUD);
    select_port(_UART1);
    Init_UART1();
    while(1) {
        if(Letter == 'A') {
            printf("Hello World! %c 1", Letter);
            Clear_Message();
            PAOUT = ~0x80; delay_ms(500);
            PAOUT = ~0x40; delay_ms(500);
            PAOUT = ~0x20; delay_ms(500);
            PAOUT = ~0x10; delay_ms(500);
            printf("Hello World! %c 2", Letter);
        }
        PAOUT = ~0x80; delay_ms(500);
        PAOUT = ~0xC0; delay_ms(500);
        PAOUT = ~0xE0; delay_ms(500);
        PAOUT = ~0xF0; delay_ms(500);
        PAOUT = ~0xF8; delay_ms(500);
        PAOUT = ~0xFC; delay_ms(500);
        PAOUT = ~0xFE; delay_ms(500);
        PAOUT = ~0xFF; delay_ms(500);
        printf("Hi! %c", Letter);
    }
}

void delay_ms(unsigned int delay) {
    unsigned int x, y;
    for(x = 0; x <= delay; x++)
        for(y = 0; y <= 512; y++);
}

#pragma interrupt
void Read_UART1(void) {
    if(U1STAT0&0x80)
        Letter = U1RXD;
}

void Init_UART1(void) {
    DI();
    SET_VECTOR(UART1_RX, Read_UART1);
    IRQ2ENH = 0x40;
    IRQ2ENL = 0x40;
    IRQ2 &= ~0x40;
    U1CTL1 &= ~0x02;
    EI();
}

void Clear_Message(void) {
    Letter = '\0';
}