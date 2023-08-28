#include <ez8.h>

void main() {
    PADD = 0x00;
    PAAF = 0x00;
    PAOC = 0x00;
    PAHDE = 0xFF;

    PBDD |= 0x01;
    PBAF &= ~0x01;

    while(1) {
        if((PBIN&0x01) == 0)
            PAOUT = ~0x55;
        else
            PAOUT = ~0xF0;
    }
}