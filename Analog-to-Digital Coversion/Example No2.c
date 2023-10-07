/*
    Multiple Channels (Temperature, Pressure, Flow Rate and Level)
*/

#include <ez8.h>
#include <sio.h>
#include <stdio.h>

void initAdcT(void);
void initAdcP(void);
void initAdcF(void);
void initAdcL(void);

void delay_ms(unsigned int delay);
unsigned int ADCout(void);

void main() {
    unsigned int Dvalue;
    float Volt;
    char c;
    init_uart(_UART0, _DEFFREQ, 9600);
    select_port(_UART0);
    while(1) {
        c = getch();
        if(c == 'T') {
            initAdcT();
            DValue = ADCout();
            Volt = DValue / 512.0;
            printf("Temperature: the equivalent digital value in hex of %6.2fVolts is 0x%03X\n", Volt, DValue);
        } else if(c == 'P') {
            initAdcP();
            DValue = ADCout();
            Volt = DValue / 512.0;
            printf("Pressure: the equivalent digital value in hex of %6.2fVolts is 0x%03X\n", Volt, DValue);
        } else if (c == 'F') {
            initAdcF();
            DValue = ADCout();
            Volt = DValue / 512.0;
            printf("Flow Rate: the equivalent digital value in hex of %6.2fVolts is 0x%03X\n", Volt, DValue);
        } else if(c == 'L') {
            initAdcL();
            DValue = ADCout();
            Volt = DValue / 512.0;
            printf("Level: the equivalent digital value in hex of %6.2fVolts is 0x%03X\n", Volt, DValue);
        }
    }
}

void initAdcT(void) {
    PBAF |= 0x01;
    ACTL = 0x00;
}

void initAdcP(void) {
    PBAF |= 0x02;
    ACTL = 0x01;
}

void initAdcF(void) {
    PBAF |= 0x04;
    ACTL = 0x02;
}

void initAdcL(void) {
    PBAF |= 0x08;
    ACTL = 0x03;
}

unsigned int ADCout(void) {
    unsigned int value;
    ACTL |= 0x80;
    while(ACTL&0x80);
    value = ((ADLR >> 6) | (ADHR << 2));
    return value;
}

void delay_ms(unsigned int delay) {
    unsigned int x, y;
    for(x = 0; x <= delay; x++)
        for(y = 0; y <= 512; y++);
}