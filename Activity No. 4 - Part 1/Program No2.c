#include <ez8.h>

void initSW(void);
void delay_ms(unsigned int delay);

#pragma interrupt
void isrSW0(void) {
    DI();
    // C. Clockwise 7 Steps 0.4s Interval
    PCOUT |= 0x01; PCOUT &= 0xF1; delay_ms(400);
    PCOUT |= 0x02; PCOUT &= 0xF2; delay_ms(400);
    PCOUT |= 0x04; PCOUT &= 0xF4; delay_ms(400);
    PCOUT |= 0x08; PCOUT &= 0xF8; delay_ms(400);
    PCOUT |= 0x01; PCOUT &= 0xF1; delay_ms(400);
    PCOUT |= 0x02; PCOUT &= 0xF2; delay_ms(400);
    PCOUT |= 0x04; PCOUT &= 0xF4; delay_ms(400);
    PCOUT |= 0x08; PCOUT &= 0xF8; delay_ms(400);
    EI();
}

#pragma interrupt
void isrSW1(void) {
    DI();
    // Motor 1 Clockwise, Motor 2 C. Clockwise 3s Duration
    PAOUT |= 0x09; PAOUT &= 0xF9; delay_ms(3000);
    EI();
}

#pragma interrupt
void isrSW2(void) {
    DI();
    // Motor 1 C. Clockwise, Motor 2 Clockwise 2s Duration
    PAOUT |= 0x06; PAOUT &= 0xF6; delay_ms(2000);
    EI();
}

void main() {
    PCDD &= 0xF0;
    PCAF &= 0xF0;
    PCOC &= 0xF0;
    PCHDE |= 0x0F;

    PADD &= 0xF0;
    PAAF &= 0xF0;
    PAOC &= 0xF0;
    PAHDE |= 0x0F;
    initSW();
}

void initSW(void) {
    DI();
    PDDD |= 0x07;
    SET_VECTOR(P0AD, isrSW0); // Medium Priority
    SET_VECTOR(P1AD, isrSW1); // Low Priority
    SET_VECTOR(P2AD, isrSW2); // High Priority
    IRQ1ENL = 0x06;
    IRQ1ENH = 0x05;
    IRQES = 0x00;
    IRQPS = 0x03; // PD.0, PD.1, PD.2
    IRQ1 &= ~0x07;
    EI();
}

void delay_ms(unsigned int delay) {
    unsigned int x, y;
    for(x = 0; x <= delay; x++)
        for(y = 0; y <= 512; y++);
}