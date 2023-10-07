#include <ez8.h>
#include <sio.h>
#include <stdio.h>

#define Sensor1 (PCIN&0x02)
#define Sensor0 (PCIN&0x01)

void main() {
    PCDD |= 0x03;
    PCAF &= ~0x03;

    PAAF |= 0x30;
    init_uart(_UART0, _DEFFREQ, _DEFBAUD);
    select_port(_UART0);
    while(1) {
        if((Sensor1 == 0) && (Sensor0 == 0))
            printf("First Name");
        else if((Sensor1 == 0) && (Sensor0 != 0))
            printf("Surname");
        else if((Sensor1 != 0) && (Sensor0 == 0))
            printf("Student Number");
        else if((Sensor != 0) && (Sensor0 != 0))
            printf("Date submission");
    }
}