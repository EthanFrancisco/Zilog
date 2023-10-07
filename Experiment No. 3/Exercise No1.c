// WIP

#include <ez8.h>
#include <sio.h>
#include <stdio.h>

#define CHANNEL 0x00
#define MODE    0x00
#define VREF    0x00
#define ENABLE  0x00

void initADC(void);
void delay_ms(unsigned int delay);
unsigned int analogRead(void);

void main() {
    unsigned int dValue = 0;

    PADD = 0x00;
    PAAF = 0x00;
    PAOC = 0x00;
    PAHDE = 0xFF;

    initADC();
    while(1) {
        dValue = analogRead();
        if(dValue < 300) {
            PAOUT = ~0xFF;
        } else if((dValue >= 300) && (dValue < 600)) {
            PAOUT = ~0xA0; delay_ms(500);
            PAOUT = ~0x50; delay_ms(500);
            PAOUT = ~0x28; delay_ms(500);
            PAOUT = ~0x14; delay_ms(500);
            PAOUT = ~0x0A; delay_ms(500);
            PAOUT = ~0x05; delay_ms(500);
        } else if((dValue >= 600) && (dValue < 900)) {
            PAOUT = ~0x80; delay_ms(500);
            PAOUT = ~0xC0; delay_ms(500);
            PAOUT = ~0xE0; delay_ms(500);
            PAOUT = ~0xF0; delay_ms(500);
            PAOUT = ~0xF8; delay_ms(500);
            PAOUT = ~0xFC; delay_ms(500);
            PAOUT = ~0xFE; delay_ms(500);
            PAOUT = ~0xFF; delay_ms(500);
        } else if(dValue >= 900) {
            PAOUT = ~0x03; delay_ms(500);
            PAOUT = ~0x06; delay_ms(500);
            PAOUT = ~0x0C; delay_ms(500);
            PAOUT = ~0x18; delay_ms(500);
            PAOUT = ~0x30; delay_ms(500);
            PAOUT = ~0x60; delay_ms(500);
            PAOUT = ~0xC0; delay_ms(500);
        }
    }
}

void initADC(void) {
    PBAF |= 0x10;
    ACTL = (CHANNEL | MODE | VREF);
}

unsigned int analogRead(void) {
    ACTL |= ENABLE;
    while(ACTL&ENABLE);
    return (((unsigned int) ADHR << 2) | (ADLR >> 6));
}

void delay_ms(unsigned int delay) {
    unsigned int x, y;
    for(x = 0; x <= delay; x++)
        for(y = 0; y <= 512; y++);
}