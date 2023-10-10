#include <ez8.h>
#include <sio.h>
#include <stdio.h>

int userInput;

void main() {
    init_uart(_UART0, _DEFFREQ, _DEFBAUD);
    select_port(_UART0);

    // Changed to Port C from Port A (Z8F0822 Compatibility)
    PCDD &= 0xF0;
    PCAF &= 0xF0;
    PCOC &= 0xF0;
    PCHDE |= 0x0F;

    PADD |= 0x30;
    PAAF &= ~0x30;
    while(1) {
        scanf("%d", &userInput);

        switch(userInput) {
            case 1:
                // Clockwise 12 Steps (1-coil excitation)
                PCOUT |= 0x01;  PCOUT &= 0xF1;
                PCOUT |= 0x02;  PCOUT &= 0xF2;
                PCOUT |= 0x04;  PCOUT &= 0xF4;
                PCOUT |= 0x08;  PCOUT &= 0xF8;
                PCOUT |= 0x01;  PCOUT &= 0xF1;
                PCOUT |= 0x02;  PCOUT &= 0xF2;
                PCOUT |= 0x04;  PCOUT &= 0xF4;
                PCOUT |= 0x08;  PCOUT &= 0xF8;
                PCOUT |= 0x01;  PCOUT &= 0xF1;
                PCOUT |= 0x02;  PCOUT &= 0xF2;
                PCOUT |= 0x04;  PCOUT &= 0xF4;
                PCOUT |= 0x08;  PCOUT &= 0xF8;
                PCOUT |= 0x01;  PCOUT &= 0xF1;
                break;
            case 2:
                // C. Clockwise 9 Steps (2-coil excitation)
                PCOUT |= 0x09;  PCOUT &= 0xF9;
                PCOUT |= 0x0C;  PCOUT &= 0xFC;
                PCOUT |= 0x06;  PCOUT &= 0xF6;
                PCOUT |= 0x03;  PCOUT &= 0xF3;
                PCOUT |= 0x09;  PCOUT &= 0xF9;
                PCOUT |= 0x0C;  PCOUT &= 0xFC;
                PCOUT |= 0x03;  PCOUT &= 0xF3;
                PCOUT |= 0x09;  PCOUT &= 0xF9;
                PCOUT |= 0x0C;  PCOUT &= 0xFC;
                PCOUT |= 0x06;  PCOUT &= 0xF6;
                break;
            case 3:
                // C. Clockwise 15 Steps (half step)
                PCOUT |= 0x01;  PCOUT &= 0xF1;
                PCOUT |= 0x03;  PCOUT &= 0xF3;
                PCOUT |= 0x02;  PCOUT &= 0xF2;
                PCOUT |= 0x06;  PCOUT &= 0xF6;
                PCOUT |= 0x04;  PCOUT &= 0xF4;
                PCOUT |= 0x0C;  PCOUT &= 0xFC;
                PCOUT |= 0x08;  PCOUT &= 0xF8;
                PCOUT |= 0x09;  PCOUT &= 0xF9;
                PCOUT |= 0x01;  PCOUT &= 0xF1;
                PCOUT |= 0x03;  PCOUT &= 0xF3;
                PCOUT |= 0x02;  PCOUT &= 0xF2;
                PCOUT |= 0x06;  PCOUT &= 0xF6;
                PCOUT |= 0x04;  PCOUT &= 0xF4;
                PCOUT |= 0x0C;  PCOUT &= 0xFC;
                PCOUT |= 0x08;  PCOUT &= 0xF8;
                PCOUT |= 0x09;  PCOUT &= 0xF9;
                break;
            default:
                // Stop
                break;
        }
    }
}