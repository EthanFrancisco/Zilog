#include <ez8.h>
#define sw1 (PBIN&0x01)
#define sw2 (PBIN&0x02)
#define sw3 (PBIN&0x04)

void main() {
    PCDD &= 0xF0;
    PCAF &= 0xF0;
    PCOC &= 0xF0;
    PCHDE |= 0x0F;

    PBDD |= 0x07;
    PBAF &= 0xF8;
    while(1) {
        if((sw3 != 0) && (sw2 != 0) && (sw1 == 0))
            PCOUT = 0x05;
        else if((sw3 != 0) && (sw2 == 0) && (sw1 != 0))
            PCOUT = 0x0A;
        else if((sw3 == 0) && (sw2 != 0) && (sw1 != 0))
            PCOUT = 0x09;
        else if((sw3 == 0) && (sw2 != 0) && (sw1 == 0))
            PCOUT = 0x06;
        else
            PCOUT = 0x00;
    }
}