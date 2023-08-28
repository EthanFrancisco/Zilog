#include <ez8.h>

void delay_ms(unsigned int delay);

void main() {
    PADD = 0x00;
    PAAF = 0x00;
    PAOC = 0x00;
    PAHDE = 0xFF;

    while(1) {
        unsigned int i, j, k, l, seq1;
        for(i = 0; i < 2; i++) {
            seq1 = ~0xC0;
            PAOUT = ~0xC0;
            delay_ms(1000);
            for(j = 0; j < 6; j++) {
                seq1 = seq1 >> 1;
                PAOUT = seq1;
                delay_ms(1000);
            }
        }
        for(k = 0; k < 4; k++) {
            PAOUT = ~0x55; delay_ms(1000);
            PAOUT ^= ~0x00; delay_ms(1000);
        }
        for(l = 0; l < 3; l++) {
            PAOUT = ~0x81; delay_ms(1000);
            PAOUT = ~0xC3; delay_ms(1000);
            PAOUT = ~0xE7; delay_ms(1000);
            PAOUT = ~0xFF; delay_ms(1000);
        }
    }
}

void delay_ms(unsigned int delay) {
    unsigned int x, y;
    for(x = 0; x <= delay; x++)
        for(y = 0; y <= 512; y++);
}