#include <ez8.h>
#include <sio.h>
#include <stdio.h>
#define sensorR (PCIN0x01)
#define sensorC (PCIN0x02)
#define sensorL (PCIN0x04)

void main() {
    init_uart(_UART0, _DEFFREQ, _DEFBAUD);
    select_port(_UART0);

    PADD |= 0x30;
    PAAF &= ~0x30;
    while(1) {
        if((sensorL == 0) && (sensorC == 0) && (sensorR))
            printf("Programmer's Name: \n");
        else if((sensorL == 0) && (sensorC == 0) && (sensorR != 0)) {
            printf("Member's Names: \n");
            printf("Member's Names: \n");
            printf("Member's Names: \n");
        } else if((sensorL == 0) && (sensorC != 0) && (sensorR == 0)) {
            printf("Student Numbers: \n");
            printf("Student Numbers: \n");
            printf("Student Numbers: \n");
            printf("Student Numbers: \n");
        } else if((sensorL == 0) && (sensorC != 0) && (sensorR != 0))
            printf("Date Performed: \n");
        else if((sensorL != 0) && (sensorC == 0) && (sensorR == 0))
            printf("Left Sensor is activated\n");
        else if((sensorL != 0) && (sensorC == 0) && (sensorR != 0))
            printf("Center Sensor is not activated\n");
        else if((sensorL != 0) && (sensorC != 0) && (sensorR == 0))
            printf("Right Sensor is not activated\n");
        else if((sensorL != 0) && (sensorC != 0) && (sensorR != 0))
            printf("All Sensors are activated\n");
    }
}