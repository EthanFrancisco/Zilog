#include <ez8.h>
#include <sio.h>
#include <stdio.h>

void delay_ms(unsigned int delay);

void main() {
    PADD = 0x00;
    PAAF = 0x00;
    PAOC = 0x00;
    PAHDE = 0xFF;

    init_uart(_UART1, _DEFFREQ, _DEFBAUD);
    select_port(_UART1);
    while(1) {
        c = getch();
        if(c == 'A') {
            PAOUT = ~0x80; delay_ms(500);
            PAOUT = ~0x40; delay_ms(500);
            PAOUT = ~0x20; delay_ms(500);
            PAOUT = ~0x10; delay_ms(500);
            printf("Hello World!");
        }
        PAOUT = ~0x80; delay_ms(500);
        PAOUT = ~0xC0; delay_ms(500);
        PAOUT = ~0xE0; delay_ms(500);
        PAOUT = ~0xF0; delay_ms(500);
        PAOUT = ~0xF8; delay_ms(500);
        PAOUT = ~0xFC; delay_ms(500);
        PAOUT = ~0xFE; delay_ms(500);
        PAOUT = ~0xFF; delay_ms(500);
    }
}

void delay_ms(unsigned int delay) {
    unsigned int x, y;
    for(x = 0; x <= delay; x++)
        for(y = 0; y <= 512; y++);
}