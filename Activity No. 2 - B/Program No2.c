#include <ez8.h>
#include <stdio.h>

#define sw1 (PBIN & 0x01) // E
#define sw2 (PBIN & 0x02) // A
#define sw3 (PBIN & 0x04) // B

void delay(unsigned int ms);

void main() {
    PADD = 0xF0;
    PAAF = 0x00;
    PAOC = 0x00;
    PAHDE = 0xFF;

    PBDD = 0x07;
    PBAF = 0x00;

    while(1) {
        if((sw1 != 0) && ((sw2 != 0) || (sw2 == 0)) && ((sw3 != 0) || (sw3 == 0))) {
            PAOUT = ~0x0F;
        }
        else if((sw1 == 0) && (sw2 == 0) && (sw3 == 0)) {
            PAOUT = ~0x07;
        }
        else if((sw1 == 0) && (sw2 == 0) && (sw3 != 0)) {
            PAOUT = ~0x03;
        }
        else if((sw1 == 0) && (sw2 != 0) && (sw3 == 0)) {
            PAOUT = ~0x0C;
        }
        else if((sw1 == 0) && (sw2 != 0) && (sw3 != 0)) {
            PAOUT = ~0x0E;
        }
    }
}

void delay(unsigned int ms) {
    unsigned int x, y;
    for(x = 0; x <= delay; x++)
        for(y = 0; y <= 512; y++);
}