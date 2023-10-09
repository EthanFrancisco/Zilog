#include <ez8.h>

#define IN1 (PBIN&0x02)
#define IN2 (PBIN&0x01)

void main() {
    PCDD &= 0xF0;
    PCAF &= 0xF0;
    PCOC &= 0xF0;
    PCHDE |= 0x0F;

    PBDD |= 0x03;
    PBAF &= ~0x03;
    while(1) {
        if((IN1 == 0) && (IN2 != 0)) {
            // Clockwise 7 steps
            PCOUT |= 0x08; PCOUT &= 0xF8;
            PCOUT |= 0x04; PCOUT &= 0xF4;
            PCOUT |= 0x02; PCOUT &= 0xF2;
            PCOUT |= 0x01; PCOUT &= 0xF1;
            PCOUT |= 0x08; PCOUT &= 0xF8;
            PCOUT |= 0x04; PCOUT &= 0xF4;
            PCOUT |= 0x02; PCOUT &= 0xF2;
            PCOUT |= 0x01; PCOUT &= 0xF1;
        } else if((IN1 != 0) && (IN2 == 0)) {
            // C. Clockwise 7 steps
            PCOUT |= 0x01; PCOUT &= 0xF1;
            PCOUT |= 0x02; PCOUT &= 0xF2;
            PCOUT |= 0x04; PCOUT &= 0xF4;
            PCOUT |= 0x08; PCOUT &= 0xF8;
            PCOUT |= 0x01; PCOUT &= 0xF1;
            PCOUT |= 0x02; PCOUT &= 0xF2;
            PCOUT |= 0x06; PCOUT &= 0xF4;
            PCOUT |= 0x08; PCOUT &= 0xF8;
        } else 
            PCOUT &= 0xF0;
    }
}