#include <ez8.h>

void delay_ms(unsigned int delay);

void main() {
    PADD = 0x00;
    PAAF = 0x00;
    PAOC = 0x00;
    PAHDE = 0xFF;

    PAOUT = 0xFF;

    while(1) {
        PAOUT &= ~0x5A; delay_ms(1000);
        PAOUT |= 0x5A; delay_ms(1000);
    }
}

void delay_ms(unsigned int delay) {
    unsigned int x, y;
    for(x = 0; x <= delay; x++)
        for(y = 0; y <= 512; y++);
}