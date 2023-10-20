#include <ez8.h>
#include <stdio.h>
#include <sio.h>

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
    T0CTL = 0x39;
    T0H = 0x00;
    T0L = 0x01;
    T0RH = 0x70;
    T0RL = 0x80;
    T0CTL |= 0x80;
}

/* Method 2
#include <ez8.h>
#include <stdio.h>
#include <sio.h>

#define PRESCALER   7
#define TMODE       0x01
#define RELOAD      28800

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
    T0CTL = (PRESCALE << 3) | TMODE;
    T0H = 0x00;
    T0L = 0x01;
    T0RH = (RELOAD >> 8);
    T0RL = RELOAD&0x00FF;
    T0CTL |= 0x80;
} */