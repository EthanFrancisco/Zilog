#include <ez8.h>
#include <sio.h>
#include <stdio.h>
#define SW0 (PBIN & 0x01)
#define SW1 (PBIN & 0x02)
#define SW2 (PBIN & 0x04)
#define SW3 (PBIN & 0x08)

void delay_ms(unsigned int delay);

void main() {
    unsigned char PrevSW0, PrevSW1, PrevSW2, PrevSW3;
    
    PADD &= ~0xFF;
    PAAF &= ~0xFF;
    PAOC &= ~0xFF;
    PAHDE |= 0xFF;
    
    PBDD |= 0x0F;
    PBAF &= ~0x0F;
    
    PAAF |= 0x30;
    
    init_uart(_UART0, _DEFFREQ, _DEFBAUD);
    select_port(_UART0);
    
    PAOUT = ~0x00;
    PrevSW0 = SW0;
    PrevSW1 = SW1;
    PrevSW2 = SW2;
    PrevSW3 = ~SW3;
    
    while(1) {
        while((PrevSW3 == SW3) && (PrevSW2 == SW2) && (PrevSW1 == SW1) && (PrevSW0 == SW0));
        if(SW0) {
            printf(" SW0 is open \t");
            PAOUT |= ~0x00;
        } else {
            printf(" SW0 is closed\t");
            PAOUT = ~0xCC; delay_ms(1000);
			PAOUT = ~0x33; delay_ms(1000);
        }
        if(SW1) {
            printf(" SW1 is open\t");
            PAOUT |= ~0x00;
        } else {
            printf(" SW1 is closed\t");
            PAOUT = ~0x03; delay_ms(1000);
			PAOUT = ~0x06; delay_ms(1000);
			PAOUT = ~0x0C; delay_ms(1000);
			PAOUT = ~0x18; delay_ms(1000);
			PAOUT = ~0x30; delay_ms(1000);
			PAOUT = ~0x60; delay_ms(1000);
			PAOUT = ~0xC0; delay_ms(1000);
        }
        if(SW2) {
            printf(" SW2 is open\t");
            PAOUT |= ~0x00;
        } else {
            printf(" SW2 is closed\t");
            PAOUT = ~0x3C; delay_ms(1000);
			PAOUT = ~0x66; delay_ms(1000);
			PAOUT = ~0xC3; delay_ms(1000);
        }
        if(SW3) {
            printf(" SW3 is open\t");
            PAOUT |= ~0x00;
        } else {
            printf(" SW3 is closed\t");
            PAOUT &= ~0x00;
        }
        putch('\n');
        PrevSW0 = SW0;
        PrevSW1 = SW1;
        PrevSW2 = SW2;
        PrevSW3 = SW3;
    }
}

void delay_ms(unsigned int delay) {
	unsigned int x, y;
	for(x = 0; x <= delay; x++)
		for(y = 0; y <= 512; y++);
}
