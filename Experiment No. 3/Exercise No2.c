#include <ez8.h>
#include <sio.h>
#include <stdio.h>

#define CHANNEL1    0x01
#define CHANNEL0    0x00
#define MODE    0x00
#define VREF    0x00
#define ENABLE  0x80

#define sensorThreshold 512     // Adjustable per conveyor width
#define conveyorRuntime 15000   // Adjustable per conveyor length

void initADC1(void);
void initADC0(void);
unsigned int analogRead(void);
void delay_ms(unsigned int delay);

void main() {
    unsigned int dValueStart, dValueEnd, conveyorObject = 0;
    PADD &= 0xF0;
    PAAF &= 0xF0;
    PAOC &= 0xF0;
    PAHDE |= 0x0F;
    while(1) {
        initADC1(); dValueEnd = analogRead();
        initADC0(); dValueStart = analogRead();
        while(conveyorObject) {
            // conveyorObject > 1 then run both motors otherwise stop both motors
            if((dValueStart >= sensorThreshold) && (dValueEnd <= sensorThreshold)) {
                // Increment conveyorObject and run both motors
                PAOUT |= 0x0F;
                delay_ms(conveyorRuntime);
                conveyorObject++;
            } else if((dValueStart <= sensorThreshold) && (dValueEnd >= sensorThreshold)) {
                // Decrement conveyorObject
                conveyorObject--;
            } else if((dValueStart >= sensorThreshold) && (dValueEnd >= sensorThreshold)) {
                // Increment conveyorObject and run both motors
                PAOUT |= 0x0F;
                delay_ms(conveyorRuntime);
                conveyorObject++;
            }
        }
        PAOUT &= 0xF0; // Stop both motors
        if(dValueStart >= sensorThreshold) {
            conveyorObject++
        }
    }
}

void initADC1(void) {
    PBAF |= 0x02;
    ACTL = (CHANNEL1 | MODE | VREF);
}

void initADC0(void) {
    PBAF |= 0x01;
    ACTL = (CHANNEL0 | MODE | VREF);
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