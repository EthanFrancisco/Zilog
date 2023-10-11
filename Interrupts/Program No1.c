#include <ez8.h>
void InitSW(void);
void initLEDports(void);
void blankLEDs(void);

#pragma interrupt
void isrSW4(void) {
    DI();
    PAOUT = ~PBIN;
    EI();
}

#pragma interrupt
void isrSW5(void) {
    DI();
    PAOUT = PBIN;
    EI();
}

void main() {
    initLEDports();
    blankLEDs();
    InitSW();
}

void InitSW(void) {
    DI();
    PDDD |= 0x30;
    SET_VECTOR(P4AD, isrSW4);
    SET_VECTOR(P5AD, isrSW5);
    IRQ1ENL = 0x30;
    IRQ1ENH = 0x30;
    IRQES = 0x10;
    IRQPS = 0x30;
    IRQ1 &= ~0x30;
    EI();
}

void initLEDports(void) {
    PADD = 0x00;
    PAAF = 0x00;
    PAOC = 0x00;
    PAHDE = 0xFF;

    PBDD = 0xFF;
    PBAF = 0x00;
}

void blankLEDs(void) {
    PAOUT = ~0x00;
}