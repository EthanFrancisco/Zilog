#include <ez8.h>

#define sw1 (PBIN&0x01)
#define sw2 (PBIN&0x02)
#define sw3 (PBIN&0x04)
#define sw4 (PBIN&0x08)

void delay_ms(unsigned int delay);

void main() {
    PADD = 0x00;
    PAAF = 0x00;
    PAOC = 0x00;
    PAHDE = 0xFF;
    
    PBDD |= 0x0F;
    PBAF &= 0xF0;
    
    while(1) {
        unsigned int i, j, seq1;
        if((sw4 != 0) && (sw3 != 0) && (sw2 != 0) && (sw1 == 0)) {
            PAOUT = ~0xCC; delay_ms(1000);
            PAOUT ^= ~0x00; delay_ms(1000);
        }
        else if((sw4 != 0) && (sw3 != 0) && (sw2 == 0) && (sw1 != 0)) {
            PAOUT = ~0x03; delay_ms(1000);
            PAOUT = ~0x06; delay_ms(1000);
            PAOUT = ~0x0C; delay_ms(1000);
            PAOUT = ~0x18; delay_ms(1000);
            PAOUT = ~0x30; delay_ms(1000);
            PAOUT = ~0x60; delay_ms(1000);
            PAOUT = ~0xC0; delay_ms(1000);
        }
        else if((sw4 != 0) && (sw3 == 0) && (sw2 != 0) && (sw1 != 0)) {
            PAOUT = ~0x3C; delay_ms(1000);
            PAOUT = ~0x66; delay_ms(1000);
            PAOUT = ~0xC3; delay_ms(1000);
        }
        else if((sw4 != 0) && (sw3 != 0) && (sw2 != 0) && (sw1 != 0)) {
            PAOUT = ~0x00; delay_ms(1000);
        } else {
            PAOUT = ~0x00;
        }
    }
}

void delay_ms(unsigned int delay) {
    unsigned int x, y;
    for(x = 0; x <= delay; x++)
        for(y = 0; y <= 512; y++);
}