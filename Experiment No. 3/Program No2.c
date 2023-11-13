#include <ez8.h>
#include <sio.h>
#include <stdio.h>

#define CHANNEL3    0x03
#define CHANNEL2    0x02
#define CHANNEL1    0x01
#define CHANNEL0    0x00
#define MODE    0x00
#define VREF    0x00
#define ENABLE  0x00

void initADC3(void);
void initADC2(void);
void initADC1(void);
void initADC0(void);

unsigned int analogRead(void);

void main() {
    unsigned int dValue = 0;
    unsigned char inpChar;

    PAAF |= 0x30;

    init_uart(_UART0, _DEFFREQ, _DEFBAUD);
    select_port(_UART0);
    while(1) {
        inpChar = getch();
        if(inpChar == 'A') {
            initADC3();
            dValue = analogRead();
            printf("Chan 3: 0x%02X\n", dValue);
        } else if(inpChar == 'D') {
            initADC2();
            dValue = analogRead();
            printf("Chan 2: 0x%02X\n", dValue);
        } else if(inpChar == 'W') {
            initADC1();
            dValue = analogRead();
            printf("Chan 1: 0x%02X\n", dValue);
        } else if(inpChar == 'S') {
            initADC0();
            dValue = analogRead();
            printf("Chan 0: 0x%02X\n", dValue);
        }
    }
}

void initADC3() {
    PBAF |= 0x08;
    ACTL = (CHANNEL3 | MODE | VREF);
}

void initADC2() {
    PBAF |= 0x04;
    ACTL = (CHANNEL2 | MODE | VREF);
}

void initADC1() {
    PBAF |= 0x02;
    ACTL = (CHANNEL1 | MODE | VREF);
}

void initADC0() {
    PBAF |= 0x01;
    ACTL = (CHANNEL0 | MODE | VREF);
}

unsigned int analogRead(void) {
    ACTL |= ENABLE;
    while(ACTL&ENABLE);
    return (((unsigned int) ADHR << 2) | (ADLR >> 6));
}