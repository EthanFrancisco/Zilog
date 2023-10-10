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
            case W:
                // DC Motor 2 (Clockwise), DC Motor 1 (Clockwise), Forward
                PCOUT |= 0x05;  PCOUT &= 0xF5;
                break;
            case A:
                // DC Motor 2 (Stop), DC Motor 1 (Clockwise), Turn Left
                PCOUT |= 0x01;  PCOUT &= 0xF1;
                break;
            case D:
                // DC Motor 2 (Clockwise), DC Motor 1 (Stop), Turn Right
                PCOUT |= 0x04;  PCOUT &= 0xF4;
                break;
            case S:
                // DC Motor 2 (C. Clockwise), DC Motor 1 (C. Clockwise), Reverse
                PCOUT |= 0x0A;  PCOUT &= 0xFA;
                break;
            default:
                // DC Motor 2 (Stop), DC Motor 1 (Stop), Stop
                PCOUT |= 0x0F;  PCOUT &= 0xFF;
                break;
        }
    }
}