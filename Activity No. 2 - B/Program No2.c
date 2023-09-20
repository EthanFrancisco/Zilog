/*
	E A B  D0 D1 D2 D3
	1 X X  1  1  1  1
	0 0 0  0  1  1  1
	0 0 1  1  0  1  1
	0 1 0  1  1  0  1
	0 1 1  1  1  1  0
*/

#include <ez8.h>
#include <stdio.h>

#define sw1 (PBIN & 0x04) // E
#define sw2 (PBIN & 0x02) // A
#define sw3 (PBIN & 0x01) // B

void delay(unsigned int ms);

void main() {
    PADD = 0x0F;
    PAAF = 0x00;
    PAOC = 0x00;
    PAHDE = 0xF0;

    PBDD = 0x07;
    PBAF = 0x00;

    while(1) {
        if((sw1 == 0) && ((sw2 != 0) || (sw2 == 0)) && ((sw3 != 0) || (sw3 == 0))) {
            PAOUT = ~0xF0;
            printf("PAOUT = %02X\n", PAOUT);
            delay(1000);
        }
        if((sw1 != 0) && (sw2 != 0) && (sw3 != 0)) {
            PAOUT = ~0x70;
            printf("PAOUT = %02X\n", PAOUT);
            delay(1000);
        }
        else if((sw1 != 0) && (sw2 != 0) && (sw3 == 0)) {
            PAOUT = ~0xB0;
            printf("PAOUT = %02X\n", PAOUT);
            delay(1000);
        }
        else if((sw1 != 0) && (sw2 == 0) && (sw3 != 0)) {
            PAOUT = ~0xD0;
            printf("PAOUT = %02X\n", PAOUT);
            delay(1000);
        }
        else if((sw1 != 0) && (sw2 == 0) && (sw3 == 0)) {
            PAOUT = ~0xE0;
            printf("PAOUT = %02X\n", PAOUT);
            delay(1000);
        }
    }
}

void delay(unsigned int ms) {
    unsigned int x, y;
    for(x = 0; x <= ms; x++)
        for(y = 0; y <= 512; y++);
}