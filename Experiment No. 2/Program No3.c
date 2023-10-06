#include <ez8.h>
#include <stdio.h>
#include <sio.h>
#define sensorR (PCIN&0x10)
#define sensorC (PCIN&0x20)
#define sensorL (PCIN&0x40)

void delay_ms(unsigned int delay);

void main() {
    init_uart(_UART1, _DEFFREQ, _DEFBAUD);
    select_port(_UART1);

    PCDD &= 0xF0;
    PCAF &= 0xF0;
    PCOC &= 0xF0;
    PCHDE |= 0x0F;

    PCDD |= 0x70;
    PCAF &= ~0x70;
    while(1) {
        if((sensorL != 0) && (sensorC != 0) && (sensorR == 0)) {
            printf("Right Sensor is activated\n");
            printf("Stepper motor is rotating in clockwise direction\n");
            printf("with 2-coil excitation\n");

            PCOUT = 0x03; delay_ms(500);
            PCOUT = 0x06; delay_ms(500);
            PCOUT = 0x0C; delay_ms(500);
            PCOUT = 0x09; delay_ms(500);
        } else if((sensorL != 0) && (sensorC == 0) && (sensorR != 0)) {
            printf("Center Sensor is activated\n");
            printf("Stepper motor is rotating in c. clockwise direction\n");
            printf("with 2-coil excitation\n");

            PCOUT = 0x09; delay_ms(500);
            PCOUT = 0x0C; delay_ms(500);
            PCOUT = 0x06; delay_ms(500);
            PCOUT = 0x03; delay_ms(500);
        } else if((sensorL == 0) && (sensorC != 0) && (sensorR != 0)) {
            printf("Left Sensor is activated\n");
            printf("Stepper motor is rotating in clockwise direction\n");
            printf("with 1-coil excitation\n");

            PCOUT = 0x01; delay_ms(500);
            PCOUT = 0x02; delay_ms(500);
            PCOUT = 0x04; delay_ms(500);
            PCOUT = 0x08; delay_ms(500);
        } else if((sensorL == 0) && (sensorC != 0) && (sensorR == 0)) {
            printf("Both Right and Left Sensors are activated\n");
            printf("Stepper motor is rotating in c. clockwise direction\n");
            printf("with 1-coil excitation\n");

            PCOUT = 0x08; delay_ms(500);
            PCOUT = 0x04; delay_ms(500);
            PCOUT = 0x02; delay_ms(500);
            PCOUT = 0x01; delay_ms(500);
        } else
            PCOUT = 0x00;
    }
}

void delay_ms(unsigned int delay) {
    unsigned int x, y;
    for(x = 0; x <= delay; x++)
        for(y = 0; y <= 512; y++);
}