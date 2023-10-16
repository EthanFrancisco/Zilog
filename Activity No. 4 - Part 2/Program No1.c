#include <ez8.h>
#include <sio.h>
#include <stdio.h>
#include <string.h>

unsigned int MessageIndex = 0, MSG_LEN = 50;
char Message[50];

void Init_UART0(void);
int POUT = ~0x55;

void main() {
    PADD = 0x00;
    PAAF = 0x00;
    PAOC = 0x00;
    PAHDE = 0xFF;

    init_uart(_UART0, _DEFFREQ, _DEFBAUD);
    select_port(_UART0);
    Init_UART0();
    PAOUT = ~POUT;
    while(1) {
        if(strstr(Message, "A") != 0) {
            PAOUT = (POUT &= 0xEC);
        } else if(strstr(Message, "E") != 0) {
            PAOUT = (POUT |= 0x2C);
        } else if(strstr(Message, "I") != 0) {
            PAOUT = (POUT ^= 0x52);
        } else if(strstr(Message, "O") != 0) {
            PAOUT = (POUT <<= 3);
        } else if(strstr(Message, "U") != 0) {
            PAOUT = (POUT >>= 4);
        }
    }
}

#pragma interrupt
void Read_UART0(void) {
    if(U0STAT0&0x80)
        Message[MessageIndex++] = U0RXD;
}

void Init_UART0(void) {
    DI();
    SET_VECTOR(UART0_RX, Read_UART0);
    IRQ0ENH = 0x10;
    IRQ0ENL = 0x00;
    IRQ0 &= ~0x10;
    EI();
}