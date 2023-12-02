#include <ez8.h>
#include <sio.h>
#include <stdio.h>

#define sensorThreshold 750

void initADC(void);
void delay_ms(unsigned int delay);

#pragma interrupt
void isrADC(void) {
    unsigned int dValue;
    dValue = ((ADHR >> 6) | (ADLR << 2));
    PAOUT = ~0xF0;
    if((dValue < sensorThreshold) && (dValue >= sensorThreshold) && (dValue < sensorThreshold)) {
        PAOUT = 0x3C; // Center Line
    } else if((dValue >= sensorThreshold) && (dValue < sensorThreshold) && (dValue < sensorThreshold)) {
        PAOUT = 0xF0; // Left Line
    } else if((dValue < sensorThreshold) && (dValue < sensorThreshold) && (dValue >= sensorThreshold)) {
        PAOUT = 0x0F; // Right Line
    }
}

void main() {
    PADD = 0x00;
    PAAF = 0x00;
    PAOC = 0x00;
    PAHDE = 0xFF;
    initADC();
    while(1) {
        ACTL |= 0x80;
        delay_ms(1000);
    }
}

void initADC(void) {
    PBAF |= 0x07;
    ACTL = 0x10;
    DI();
    SET_VECTOR(ADC, isrADC);
    IRQ0ENH = 0x01;
    IRQ0ENL = 0x01;
    IRQ0 &= ~0x01;
    EI();
}

void delay_ms(unsigned int delay) {
    unsigned int x, y;
    for(x = 0; x <= delay; x++)
        for(y = 0; y <= 512; y++);
}