#include <ez8.h>
#include <sio.h>
#include <stdio.h>

int userInput;

void delay_ms(unsigned int delay);

void main() {
    init_uart(_UART0, _DEFFREQ, _DEFBAUD);
    select_port(_UART0);

    // Changed to Port C from Port A (Z8F0822 Compatibility)
    PCDD &= ~0x0F;
    PCAF &= ~0x0F;
    PCOC &= ~0x0F;
    PCHDE |= 0x0F;

    PADD |= 0x30;
    PAAF &= ~0x30;
    while(1) {
        scanf("%d", &userInput);

        switch(userInput) {
            case 1:
                // Clockwise 12 Steps (1-coil excitation)
                PCOUT = 0x01; delay_ms(500);
                PCOUT = 0x02; delay_ms(500);
                PCOUT = 0x04; delay_ms(500);
                PCOUT = 0x08; delay_ms(500);
                PCOUT = 0x01; delay_ms(500);
                PCOUT = 0x02; delay_ms(500);
                PCOUT = 0x04; delay_ms(500);
                PCOUT = 0x08; delay_ms(500);
                PCOUT = 0x01; delay_ms(500);
                PCOUT = 0x02; delay_ms(500);
                PCOUT = 0x04; delay_ms(500);
                PCOUT = 0x08; delay_ms(500);
                break;
            case 2:
                // C. Clockwise 9 Steps (2-coil excitation)
                PCOUT = 0x09; delay_ms(500);
                PCOUT = 0x0C; delay_ms(500);
                PCOUT = 0x06; delay_ms(500);
                PCOUT = 0x03; delay_ms(500);
                PCOUT = 0x09; delay_ms(500);
                PCOUT = 0x0C; delay_ms(500);
                PCOUT = 0x03; delay_ms(500);
                PCOUT = 0x09; delay_ms(500);
                PCOUT = 0x0C; delay_ms(500);
                break;
            case 3:
                // C. Clockwise 15 Steps (half step)
                PCOUT = 0x01; delay_ms(500);
                PCOUT = 0x03; delay_ms(500);
                PCOUT = 0x02; delay_ms(500);
                PCOUT = 0x06; delay_ms(500);
                PCOUT = 0x04; delay_ms(500);
                PCOUT = 0x0C; delay_ms(500);
                PCOUT = 0x08; delay_ms(500);
                PCOUT = 0x09; delay_ms(500);
                PCOUT = 0x01; delay_ms(500);
                PCOUT = 0x03; delay_ms(500);
                PCOUT = 0x02; delay_ms(500);
                PCOUT = 0x06; delay_ms(500);
                PCOUT = 0x04; delay_ms(500);
                PCOUT = 0x0C; delay_ms(500);
                PCOUT = 0x08; delay_ms(500);
                break;
            default:
                // Stop
                break;
        }
    }
}

void delay_ms(unsigned int delay) {
    unsigned int x, y;
    for(x = 0; x <= delay; x++)
        for(y = 0; y <= 512; y++);
}