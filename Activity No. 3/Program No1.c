#include <ez8.h>

#define IN1 (PBIN&0x02)
#define IN0 (PBIN&0x01)

void delay_ms(unsigned int delay);

void main() {
    PCDD &= 0xF0;
    PCAF &= 0xF0;
    PCOC &= 0xF0;
    PCHDE |= 0x0F;

    PBDD |= 0x03;
    PBAF &= ~0x03;
    while(1) {
        if((IN1 == 0) && (IN0 != 0)) {
            // Clockwise 7 steps
            PCOUT = 0x0C; delay_ms(500);
            PCOUT = 0x06; delay_ms(500);
            PCOUT = 0x03; delay_ms(500);
            PCOUT = 0x09; delay_ms(500);
            PCOUT = 0x0C; delay_ms(500);
            PCOUT = 0x06; delay_ms(500);
            PCOUT = 0x03; delay_ms(500);
        } else if((IN1 != 0) && (IN0 == 0)) {
            // C. Clockwise 7 steps
            PCOUT = 0x09; delay_ms(500);
            PCOUT = 0x03; delay_ms(500);
            PCOUT = 0x06; delay_ms(500);
            PCOUT = 0x0C; delay_ms(500);
            PCOUT = 0x09; delay_ms(500);
            PCOUT = 0x03; delay_ms(500);
            PCOUT = 0x06; delay_ms(500);
        } else if((IN1 == 0) && (IN0 == 0))
            PCOUT = 0x00;
        else if((IN1 != 0) && (IN0 != 0))
            PCOUT = 0x00;
    }
}

void delay_ms(unsigned int delay) {
    unsigned int x, y;
    for(x = 0; x <= delay; x++)
        for(y = 0; y <= 512; y++);
}