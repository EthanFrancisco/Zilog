#include <ez8.h>
#include <sio.h>
#include <stdio.h>
#include <string.h>

unsigned int MessageIndex = 0, MSG_LEN = 50;
char Message[50];

void delay_ms(unsigned int delay);
void Init_UART0(void);

void main() {
    PADD = 0x00;
    PAAF = 0x00;
    PAOC = 0x00;
    PAHDE = 0xFF;

    init_uart(_UART0, _DEFFREQ, _DEFBAUD);
    select_port(_UART0);
    Init_UART0();
    PAOUT = ~0x00;
    while(1) {
        if(strstr(Message, "SEQ1") != 0) {
            PAOUT = ~0x80; delay_ms(500);
            PAOUT = ~0x40; delay_ms(500);
            PAOUT = ~0x20; delay_ms(500);
            PAOUT = ~0x10; delay_ms(500);
            PAOUT = ~0x08; delay_ms(500);
            PAOUT = ~0x04; delay_ms(500);
            PAOUT = ~0x02; delay_ms(500);
            PAOUT = ~0x01; delay_ms(500);
        } else if(strstr(Message, "SEQ2") != 0) {
            PAOUT = ~0x03; delay_ms(500);
            PAOUT = ~0x06; delay_ms(500);
            PAOUT = ~0x0C; delay_ms(500);
            PAOUT = ~0x18; delay_ms(500);
            PAOUT = ~0x30; delay_ms(500);
            PAOUT = ~0x60; delay_ms(500);
            PAOUT = ~0xC0; delay_ms(500);
        } else if(strstr(Message, "SEQ3") != 0) {
            PAOUT = ~0x3C; delay_ms(500);
            PAOUT = ~0x66; delay_ms(500);
            PAOUT = ~0xC3; delay_ms(500);
        }
    }
}

void delay_ms(unsigned int delay) {
    unsigned int x, y;
    for(x = 0; x <= delay; x++)
        for(y = 0; y <= 512; y++);
}

#pragma interrupt
void Read_UART0(void) {
    if(U0STAT0&0x80)
        Message[MessageIndex++] = U0RXD;
}

void Init_UART0(void) {
    DI();
    SET_VECTOR(UART0_RX, Read_UART0);
    IRQ0ENH = 0x00;
    IRQ0ENL = 0x10;
    IRQ0 &= ~0x10;
    EI();
}