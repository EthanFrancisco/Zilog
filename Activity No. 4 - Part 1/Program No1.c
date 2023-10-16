#include <ez8.h>

initSW(void);
void delay_ms(unsigned int delay);

// Port B.0 to B.3 = Upper Nibble
// Port C.0 to C.3 = Lower Nibble
#pragma interrupt
void isrSW1(void) {
    DI();
    PBOUT |= ~0x0A; delay_ms(500);
    PBOUT |= ~0x05; delay_ms(500);
    PBOUT |= ~0x02; PCOUT |= ~0x08; delay_ms(500);
    PBOUT |= ~0x01; PCOUT |= ~0x04; delay_ms(500);
    PCOUT |= ~0x0A; delay_ms(500);
    PCOUT |= ~0x05; delay_ms(500);
    EI();
}

#pragma interrupt
void isrSW2(void) {
    DI();
    PCOUT |= ~0x07; delay_ms(500);
    PCOUT |= ~0x0E; delay_ms(500);
    PBOUT |= ~0x01; PCOUT |= ~0x0C; delay_ms(500);
    PBOUT |= ~0x03; PCOUT |= ~0x08; delay_ms(500);
    PBOUT |= ~0x07; delay_ms(500);
    PBOUT |= ~0x0E; delay_ms(500);
    EI();
}

#pragma interrupt
void isrSW3(void) {
    DI();
    PBOUT |= ~0x01; PCOUT |= ~0x01; delay_ms(500);
    PBOUT |= ~0x02; PCOUT |= ~0x02; delay_ms(500);
    PBOUT |= ~0x04; PCOUT |= ~0x04; delay_ms(500);
    PBOUT |= ~0x08; PCOUT |= ~0x08; delay_ms(500);
    EI();
}

#pragma interrupt
void isrSW4(void) {
    DI();
    PBOUT |= ~0x0F; PCOUT |= 0x0F; delay_ms(500);
}

void main() {
    PBDD &= 0xF0;
    PBAF &= 0xF0;
    PBOC &= 0xF0;
    PBHDE |= 0x0F;

    PCDD &= 0xF0;
    PCAF &= 0xF0;
    PCOC &= 0xF0;
    PCHDE |= 0x0F;

    PBOUT &= 0xF0; PCOUT &= 0xF0;
    InitSW();
}

void InitSW(void) {
    DI();
    PADD |= 0xC0;
    PDDD |= 0x30;
    SET_VECTOR(P7AD, isrSW1); // Medium Priority
    SET_VECTOR(P6AD, isrSW2); // Medium Priority
    SET_VECTOR(P5AD, isrSW3); // High Priority
    SET_VECTOR(P4AD, isrSW4); // Low Priority
    IRQ1ENL = 0x30;
    IRQ1ENH = 0xE0;
    IRQES = 0x00;
    IRQPS = 0x30; // PA.7, PA.6, PD.5, PD.4
    IRQ1 &= ~0xF0;
    EI();
}

void delay_ms(unsigned int delay) {
    unsigned int x, y;
    for(x = 0; x <= delay; x++)
        for(y = 0; y <= 512; y++);
}