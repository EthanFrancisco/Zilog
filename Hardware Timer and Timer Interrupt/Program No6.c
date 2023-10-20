#include <ez8.h>
#include <stdio.h>
#include <sio.h>

#define PRESCALER   0x70
#define TMODE       0x41
#define RELOAD      28800

unsigned int counter = 0;

void InitPort(void);
void Init_Timer(void);

void main() {
    InitPort();
    Init_Timer();
    //while(1);
}

void InitPort(void) {
    PADD = 0x00;
    PAAF = 0x00;
    PAOC = 0x00;
    PAHDE = 0xFF;
    PAOUT = 0x55;
}

#pragma interrupt
void ISR_Timer(void) {
    DI();
    if(counter < 10) {
        counter++;
        PAOUT = ~0x00;
    } else {
        counter++;
        PAOUT = 0x55;
        if(counter >= 20)
            counter = 0;
    }
    EI();
}

void Init_Timer(void) {
    DI();
    T0CTL = 0x00;
    T0CTL = (PRESCALER << 3) | TMODE;
    T0H = 0x00;
    T0L = 0x01;
    T0RH = (RELOAD >> 8);
    T0RL = RELOAD&0xFF;
    SET_VECTOR(TIMER0, ISR_Timer);
    IRQ0ENH = 0x20;
    IRQ0ENL = 0x20;
    IRQ0 &= ~0x20;
    T0CTL |= 0x80;
    EI();
}