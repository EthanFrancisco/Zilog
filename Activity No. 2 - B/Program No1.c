#include <ez8.h>

#define sw1 (PBIN & 0x01) // x input
#define sw2 (PBIN & 0x02) // y input
#define sw3 (PBIN & 0x04) // z input

void delay(unsigned int ms);

void main() {
    PADD = 0x00;
    PAAF = 0x00;
    PAOC = 0x00;
    PAHDE = 0xFF;

    PBDD = 0x07;
    PBAF = 0x00;

    while(1) {
        if((sw3 == 0) && (sw2 == 0) && (sw1 == 0)) {
            PAOUT = ~0x80; // 10000000
        }
        else if((sw3 == 0) && (sw2 == 0) && (sw1 != 0)) {
            PAOUT = ~0x40; // 01000000
        }
        else if((sw3 == 0) && (sw2 != 0) && (sw1 == 0)) {
            PAOUT = ~0x20; // 00100000
        }
        else if((sw3 == 0) && (sw2 != 0) && (sw1 != 0)) {
            PAOUT = ~0x10; // 00010000
        }
        else if((sw3 != 0) && (sw2 == 0) && (sw1 == 0)) {
            PAOUT = ~0x08; // 00001000
        }
        else if((sw3 != 0) && (sw2 == 0) && (sw1 != 0)) {
            PAOUT = ~0x04; // 00000100
        }
        else if((sw3 != 0) && (sw2 != 0) && (sw1 == 0)) {
            PAOUT = ~0x02; // 00000010
        }
        else if((sw3 != 0) && (sw2 != 0) && (sw1 != 0)) {
            PAOUT = ~0x01; // 00000001
        }
    }
}

void delay(unsigned int ms) {
    unsigned int x, y;
    for(x = 0; x <= ms; x++)
        for(y = 0; y <= 512; y++);
}