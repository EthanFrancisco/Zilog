#include <ez8.h>
#include <stdio.h>
#include <sio.h>

void delay_ms(unsigned int delay);
void Init_SW(void);
void Init_port(void);

#pragma interrupt
void SW0_ISR() {
    DI();
    PBOUT = ~0x81; delay_ms(2000);
    PBOUT = ~0x42; delay_ms(2000);
    PBOUT = ~0x24; delay_ms(2000);
    PBOUT = ~0x18; delay_ms(2000);
    select_port(_UART1);
    printf("SW0 is pressed");
    EI();
}

#pragma interrupt
void SW1_ISR() {
    DI();
    select_port(_UART1);
    printf("SW1 is pressed");
    PBOUT = ~0x18; delay_ms(2000);
    PBOUT = ~0x24; delay_ms(2000);
    PBOUT = ~0x42; delay_ms(2000);
    PBOUT = ~0x81; delay_ms(2000);
    EI();
}

#pragma interrupt
void SW2_ISR() {
    DI();
    select_port(_UART0);
    printf("SW2 is pressed/released");
    EI();
}

#pragma interrupt
void SW1_ISR() {
    DI();
    select_port(_UART0);
    printf("SW3 is pressed/released");
    EI();
}

void main() {
    Init_port();
    Init_SW();
    init_uart(_UART0, _DEFFREQ, _DEFBAUD);
    init_uart(_UART1, _DEFFREQ, 9600);
}

void delay_ms(unsigned int delay) {
    unsigned int x, y;
    for(x = 0; x <= delay; x++)
        for(y = 0; y <= 512; y++);
}

void Init_SW(void) {
    DI();
    PADD |= 0x0F;
    SET_VECTOR(P0AD, SW0_ISR);
    SET_VECTOR(P1AD, SW1_ISR);
    SET_VECTOR(P2AD, SW2_ISR);
    SET_VECTOR(P3AD, SW3_ISR);
    IRQ1ENH = 0x0F;
    IRQ1ENL = 0x0E;
    IRQES = 0x0C;
    IRQPS = 0x00;
    IRQ1 &= ~0x0F;
    EI();
}

void Init_port() {
    PBDD = 0x00;
    PBAF = 0x00;
    PBOC = 0x00;
    PBHDE = 0xFF;

    PAAF |= 0x30;
    PDAF |= 0x30;
}