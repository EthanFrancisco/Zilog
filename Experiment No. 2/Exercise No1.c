#include <ez8.h>
#define sensorR (PCIN&0x01)
#define sensorC (PCIN&0x02)
#define sensorL (PCIN&0x04)

void main() {
    PADD = 0x00;
    PAAF = 0x00;
    PAOC = 0x00;
    PAHDE = 0xFF;

    PCDD |= 0x07;
    PCAF &= ~0x07;
    while(1) {
        if((sensorL == 0) && (sensorC == 0) && (sensorR == 0)) {
            PAOUT = ~0x81; delay_ms(500);
            PAOUT = ~0x42; delay_ms(500);
            PAOUT = ~0x24; delay_ms(500);
            PAOUT = ~0x18; delay_ms(500);
        } else if((sensorL == 0) && (sensorC == 0) && (sensorR != 0)) {
            PAOUT = ~0xC3; delay_ms(400);
            PAOUT = ~0x66; delay_ms(400);
            PAOUT = ~0x3C; delay_ms(400);
            PAOUT = ~0x99; delay_ms(400);
        } else if((sensorL == 0) && (sensorC != 0) && (sensorR == 0)) {
            PAOUT = ~0x18; delay_ms(300);
            PAOUT = ~0x24; delay_ms(300);
            PAOUT = ~0x42; delay_ms(300);
            PAOUT = ~0x81; delay_ms(300);
        } else if((sensorL == 0) && (sensorC != 0) && (sensorR != 0)) {
            PAOUT = ~0x99; delay_ms(200);
            PAOUT = ~0x3C; delay_ms(200);
            PAOUT = ~0x66; delay_ms(200);
            PAOUT = ~0xC3; delay_ms(200);
        } else if((sensorL != 0) && (sensorC == 0) && (sensorR == 0))
            PAOUT = ~0x99;
        else if((sensorL != 0) && (sensorC == 0) && (sensorR != 0))
            PAOUT = ~0x66;
        else if((sensorL != 0) && (sensorC != 0) && (sensorR == 0))
            PAOUT = ~0x96;
        else if((sensorL != 0) && (sensorC != 0) && (sensorR != 0))
            PAOUT = ~0x00;
    }
}

void delay_ms(unsigned int delay) {
    unsigned int x, y;
    for(x = 0; x <= delay; x++)
        for(y = 0; y <= 512; y++);
}