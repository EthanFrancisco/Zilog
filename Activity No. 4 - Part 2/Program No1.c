#include <ez8.h>
#include <sio.h>
#include <stdio.h>

char Letter;

void initSW(void);
void Init_UART0(void);

void main() {
    PADD = 0x00;
    PAAF = 0x00;
    PAOC = 0x00;
    PAHDE = 0xFF;

    PAOUT = ~0x55;
    init_uart(_UART0, _DEFFREQ, _DEFBAUD);
    select_port(_UART0);
    Init_UART0();
    while(1) {
        if(Letter == 'A') {
            PAOUT &= 0xEC; 
        } else if(Letter == 'E') {
            PAOUT |= 0x2C;
        } else if(Letter == 'I') {
            PAOUT ^= 0x52;
        } else if(Letter == 'O') {
            PAOUT <<= 3;
        } else if(Letter == 'U') {
            PAOUT >>= 4;
        }
    }
}

#pragma interrupt
void Read_UART0(void) {
    if(U0STAT0&0x80)
        Letter = U0RXD;
}

void Init_UART0(void) {
    DI();
    SET_VECTOR(UART0_RX, Read_UART0);
    IRQ0ENL = 0x00;
    IRQ0ENH = 0x10;
    IRQ0 &= ~0x10;
    EI();
}