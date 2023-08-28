#include <ez8.h>
#include <sio.h>
#include <stdio.h>

#define sw1 (PBIN&0x01)
#define sw2 (PBIN&0x02)
#define sw3 (PBIN&0x04)
#define sw4 (PBIN&0x08)

void delay_ms(unsigned int delay);

void main() {
    PCDD &= 0x00;
    PCAF &= 0x00;
    PCOC &= 0x00;
    PCHDE |= 0xFF;
    
    PBDD |= 0x0F;
    PBAF &= 0xF0;
    
    PAAF |= 0x30;
    
    init_uart(_UART0, _DEFFREQ, _DEFBAUD);
    select_port(_UART0);
    
    PCOUT = ~0x00;
    PrevSW1 = SW1;
    PrevSW2 = SW2;
    PrevSW3 = SW3;
    PrevSW4 = ~SW4;
    
    while(1) {
        while((PrevSW4 == SW4) && (PrevSW3 == SW3) && (PrevSW2 == SW2) && (PrevSW1 == SW1));
        if(SW1) {
            printf(" SW1 is closed\t");
            PCOUT = ~0xCC; delay_ms(1000);
            PCOUT ^= ~0x00; delay_ms(1000);
        } else {
            printf(" SW1 is open\t");
            PCOUT = ~0x00;
        }
        if(SW2) {
            printf(" SW2 is closed\t");
            PCOUT = ~0x03; delay_ms(1000);
            PCOUT = ~0x06; delay_ms(1000);
            PCOUT = ~0x0C; delay_ms(1000);
            PCOUT = ~0x18; delay_ms(1000);
            PCOUT = ~0x30; delay_ms(1000);
            PCOUT = ~0x60; delay_ms(1000);
            PCOUT = ~0xC0; delay_ms(1000);
        } else {
            printf(" SW2 is open\t");
            PCOUT = ~0x00;
        }
        if(SW3) {
            printf(" SW3 is closed\t");
            PAOUT = ~0x3C; delay_ms(1000);
            PAOUT = ~0x66; delay_ms(1000);
            PAOUT = ~0xC3; delay_ms(1000);
        } else {
            printf(" SW3 is open\t");
            PCOUT = ~0x00;
        }
    }
}

void delay_ms(unsigned int delay) {
    unsigned int x, y;
    for(x = 0; x <= delay; x++)
        for(y = 0; y <= 512; y++);
}