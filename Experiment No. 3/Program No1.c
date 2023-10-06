#include <ez8.h>
#include <sio.h>
#include <stdio.h>

#define CHANNEL 0x00
#define MODE    0x00
#define VREF    0x00
#define ENABLE  0x00

void initADC(void);
unsigned int analogRead(void);

void main() {
    unsigned int dValue = 0;
    float eqVoltage = 0.0;

    init_uart(_UART0, _DEFFREQ, _DEFBAUD);
    select_port(_UART0);
    initADC();

    while(getch() == 'a') {
        dValue = analogRead();
        printf("Digital Value: 0x%02X\t", dValue);
        eqVoltage = (2 * dValue) / 1024.0;
        printf("Analog input voltage is %4.3f volts\n", eqVoltage);
    }
}

void initADC(void) {
    PBAF |= 0x01;
    ACTL = (CHANNEL | MODE | VREF);
}

unsigned int analogRead(void) {
    ACTL |= ENABLE;
    while(ACTL&ENABLE);
    return (((unsigned int) ADHR << 2) | (ADLR >> 6));
}

