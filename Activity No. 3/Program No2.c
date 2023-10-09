#include <ez8.h>

#define IN1 (PBIN&0x02)
#define IN2 (PBIN&0x04)

void main() {
    PADD &= 0x0F;
    PAAF &= 0x0F;
    PAOC &= 0x0F;
    PAHDE |= 0xF0;

    PBDD |= 0x06;
    PBAF &= ~0x06;
    while(1) {
        if((IN1 == 0) && (IN2 != 0)) {
            PAOUT |= 0x10;
            PAOUT &= 0x1F;
        } else if((IN1 != 0) && (IN2 == 0)) {
            PAOUT |= 0x80;
            PAOUT &= 0x8F;
        } else if((IN1 == 0) && (IN2 == 0)) {
            PAOUT |= 0x90;
            PAOUT &= 0x9F;
        } else {
            PAOUT |= 0x60;
            PAOUT &= 0x6F;
        }
    }
}