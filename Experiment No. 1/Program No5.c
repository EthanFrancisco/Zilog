#include <ez8.h>
#define sw1 (PBIN&0x01)
#define sw2 (PBIN&0x02)
#define sw3 (PBIN&0x04)
#define sw4 (PBIN&0x08)

void main() {
    PADD = 0x00;
    PAAF = 0x00;
    PAOC = 0x00;
    PAHDE = 0xFF;

    PBDD |= 0x0F;
    PBAF &= 0xF0;

    while(1) {
        if((sw4 != 0) && (sw3 == 0) && (sw2 == 0) && (sw1 != 0))
            PAOUT = ~0x09;
        else if((sw4 == 0) && (sw3 == 0) && (sw2 != 0) && (sw1 != 0))
            PAOUT = ~0x08;
        else if((sw4 != 0) && (sw3 != 0) && (sw2 == 0) && (sw1 == 0))
            PAOUT = ~0x01;
        else if((sw4 != 0) && (sw3 != 0) && (sw2 != 0) && (sw1 != 0))
            PAOUT = ~0x06;
        else
            PAOUT = ~0x0F;
    }
}