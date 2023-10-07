#include <ez8.h>

#define IN1 (PBIN&0x02)
#define IN0 (PBIN&0x01)

void main() {
    PADD &= 0x0F;
    PAAF &= 0x0F;
    PAOC &= 0x0F;
    PAHDE |= 0xF0;

    PBDD |= 0x03;
    PBAF &= ~0x03;
    while(1) {
        if((IN1 == 0) && (IN0 != 0))
            PAOUT = 0x10;
        else if((IN1 != 0) && (IN0 == 0))
            PAOUT = 0x80;
        else if((IN1 == 0) && (IN0 == 0))
            PAOUT = 0x90;
        else if((IN1 != 0) && (IN0 != 0))
            PAOUT = 0x60;
    }
}