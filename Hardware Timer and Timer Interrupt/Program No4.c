#include <ez8.h>
#include <stdio.h>
#include <sio.h>

#define PRESCALER   0x07
#define TMODE       0x43
#define RELOAD      2880

unsigned int PWM;

void InitPort(void);
void Init_Timer(void);

void main() {
    char DATA;
    InitPort();

    init_uart(_UART1, _DEFFREQ, _DEFBAUD);
    select_port(_UART1);
    PWM = 75;
    while(1) {
        DATA = getch();
        if(DATA == 'a') {
            PWM = 75;
            Init_Timer();
        } else if(DATA == 's') {
            PWM = 120;
            Init_Timer();
        } else if(DATA == 'w') {
            PWM = 207;
            Init_Timer();
        } else if(DATA == 'x') {
            PWM = 270;
            Init_Timer();
        } else if(DATA == 'd') {
            PWM = 340;
            Init_Timer();
        }
    }
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
    T0RH = (RELOAD >> 8);
    T0RL = RELOAD&0xFF;
    T0PWMH = PWM >> 8;
    T0PWML = PWM&0x00FF;
    T0CTL |= 0x80;
}