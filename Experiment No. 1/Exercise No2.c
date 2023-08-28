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
        if((sw4 != 0) && (sw3 != 0) && (sw2 != 0) && (sw1 == 0)) {
            PAOUT = ~0xE0; delay_ms(1000);
            PAOUT = ~0x70; delay_ms(1000);
            PAOUT = ~0x38; delay_ms(1000);
            PAOUT = ~0x1C; delay_ms(1000);
            PAOUT = ~0x0E; delay_ms(1000);
            PAOUT = ~0x07; delay_ms(1000);
        }
        else if((sw4 != 0) && (sw3 != 0) && (sw2 == 0) && (sw1 != 0)) {
            PAOUT = ~0x05; delay_ms(1000);
            PAOUT = ~0x0A; delay_ms(1000);
            PAOUT = ~0x14; delay_ms(1000);
            PAOUT = ~0x28; delay_ms(1000);
            PAOUT = ~0x50; delay_ms(1000);
            PAOUT = ~0xA0; delay_ms(1000);
        }
        else if((sw4 != 0) && (sw3 == 0) && (sw2 != 0) && (sw1 != 0)) {
            PAOUT = ~0x11; delay_ms(1000);
            PAOUT = ~0x22; delay_ms(1000);
            PAOUT = ~0x44; delay_ms(1000);
            PAOUT = ~0x88; delay_ms(1000);
        }
        else if((sw4 != 0) && (sw3 != 0) && (sw2 != 0) && (sw1 != 0)) {
            PAOUT = ~0x99; delay_ms(1000);
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