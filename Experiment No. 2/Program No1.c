#include <ez8.h>
#define sensorR (PCIN&0x10)
#define sensorC (PCIN&0x20)
#define sensorL (PCIN&0x40)

void delay_ms(unsigned int delay);

void main() {
    PADD = 0x00;
    PAAF = 0x00;
    PAOC = 0x00;
    PAHDE = 0xFF;

    PCDD |= 0x70;
    PCAF &= ~0x70;
    while(1) {
        if((sensorR == 0) && (sensorC == 0) && (sensorL == 0))
            PAOUT = ~0x09;
        else if((sensorR == 0) && (sensorC != 0) && (sensorL != 0))
            PAOUT = ~0x06;
        else if((sensorR != 0) && (sensorC == 0) && (sensorL != 0)) {
            PAOUT = ~0x10; delay_ms(500);
            PAOUT = ~0x20; delay_ms(500);
            PAOUT = ~0x40; delay_ms(500);
            PAOUT = ~0x80; delay_ms(500);
        } else if((sensorR != 0) && (sensorC != 0) && (sensorL == 0)) {
            PAOUT = ~0x80; delay_ms(500);
            PAOUT = ~0x40; delay_ms(500);
            PAOUT = ~0x20; delay_ms(500);
            PAOUT = ~0x10; delay_ms(500);
        } else
            PAOUT = ~0x00;
    }
}

void delay_ms(unsigned int delay) {
    unsigned int x, y;
    for(x = 0; x <= delay; x++)
        for(y = 0; y <= 512; y++);
}