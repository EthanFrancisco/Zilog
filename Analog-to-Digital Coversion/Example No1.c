/*
    Single-shot conversion to sample the voltage
    at ANA1 (PB1). (External V_REF)
*/

#include <ez8.h>
#include <sio.h>
#include <stdio.h>

#define VREF    0x20
#define MODE    0x00
#define CHANNEL 0x01
#define CHANNEL 0x80

void Init_ADC(void);
unsigned int PollADC(void);
void delay_ms(unsigned int delay);

void main() {
    unsigned int Dvalue;
    float volts;

    Init_ADC();
    init_uart(_UART0, _DEFFREQ, _DEFBAUD);
    select_port(_UART0);
    while(1) {
        Dvalue = PollADC();
        printf("Digital Value: 0x%03X\t", Dvalue);
        volts = Dvalue / 512.0;
        printf("Voltage = %6.3f volts\n", volts);
        delay_ms(2000);
    }
}

void Init_ADC(void) {
    PBAF |= 0x02;
    ACTL = (VREF | MODE | CHANNEL);
}

unsigned int PollADC(void) {
    unsigned int value;
    ACTL |= CEN;
    while(ACTL&CEN);
    value = (ADHR << 2) | (ADLR >> 6);
    return value;
}

void delay_ms(unsigned int delay) {
    unsigned int x, y;
    for(x = 0; x <= delay; x++)
        for(y = 0; y <= 512; y++);
}