#include <ez8.h>
#include <stdio.h>
#include <sio.h>

#define PRESCALER   0x07
#define TMODE       0x43
#define RELOAD      57600
#define PWM         14400

void InitPort(void);
void Init_Timer(void);

void main() {
    InitPort();
    Init_Timer();
}

void InitPort(void) {
    PAAF |= 0x02;
    PAHDE |= 0x02;
}

void Init_Timer(void) {
    T0CTL = 0x00;
    T0CTL = (PRESCALER << 3) | TMODE;
    T0H = 0x00;
    T0L = 0x01;
    T0RH = RELOAD >> 8;
    T0RL = RELOAD&0x00FF;
    T0PWMH = PWM >> 8;
    T0PWM = PWM&0x00FF;
    T0CTL |= 0x80;
}