#include <ez8.h>
#include <sio.h>
#include <stdio.h>
#define SW0 (PBIN & 0x01)
#define SW1 (PBIN & 0x02)
#define SW2 (PBIN & 0x04)
#define SW3 (PBIN & 0x08)
void main() {
    unsigned char PrevSW0, PrevSW1, PrevSW2, PrevSW3;
    
    PCDD &= ~0x0F;
    PCAF &= ~0x0F;
    PCOC &= ~0x0F;
    PCHDE |= 0x0F;
    
    PBDD |= 0x0F;
    PBAF &= ~0x0F;
    
    PAAF |= 0x30;
    
    init_uart(_UART0, _DEFFREQ, _DEFBAUD);
    select_port(_UART0);
    
    PCOUT = ~0x00;
    PrevSW0 = SW0;
    PrevSW1 = SW1;
    PrevSW2 = SW2;
    PrevSW3 = ~SW3;
    
    while(1) {
        while((PrevSW3 == SW3) && (PrevSW2 == SW2) && (PrevSW1 == SW1) && (PrevSW0 == SW0));
        if(SW0) {
            printf(" SW0 is open \t");
            PCOUT |= 0x01;
        } else {
            printf(" SW0 is closed\t");
            PCOUT &= ~0x01;
        }
        if(SW1) {
            printf(" SW1 is open\t");
            PCOUT |= 0x02;
        } else {
            printf(" SW1 is closed\t");
            PCOUT &= 0x02;
        }
        if(SW2) {
            printf(" SW2 is open\t");
            PCOUT |= 0x04;
        } else {
            printf(" SW2 is closed\t");
            PCOUT &= 0x04;
        }
        if(SW3) {
            printf(" SW3 is open\t");
            PCOUT |= 0x08;
        } else {
            printf(" SW3 is closed\t");
            PCOUT &= 0x08;
        }
        putch('\n');
        PrevSW0 = SW0;
        PrevSW1 = SW1;
        PrevSW2 = SW2;
        PrevSW3 = SW3;
    }
}