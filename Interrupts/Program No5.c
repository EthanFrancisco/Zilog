#include <ez8.h>
#include <sio.h>
#include <stdio.h>
#include <string.h>

unsigned int MessageIndex = 0, MSG_LEN = 50;
char Message[50];

void delay_ms(unsigned int delay);
void Clear_Message(void);

void main() {
    PADD = 0x00;
    PAAF = 0x00;
    PAOC = 0x00;
    PAHDE = 0xFF;

    init_uart(_UART1, _DEFFREQ, _DEFBAUD);
    select_port(_UART1);
    while(1) {
        scanf("%s", &Message);
        if(strstr(Message, "one") != 0) {
            printf("Data: %s la\n", Message);
            Clear_Message();
            PAOUT = ~0x80;
            delay_ms(500);
            printf("Data: %s lb\n", Message);
        } else if(strstr(Message, "two") != 0) {
            printf("Data is %s 2a\n", Message);
            Clear_Message();
            PAOUT = ~0x40;
            delay_ms(500);
            printf("Data: %s 2b\n", Message);
        } else if(strstr(Message, "three") != 0) {
            printf("Data: %s 3a\n", Message);
            Clear_Message();
            PAOUT = ~0x20;
            delay_ms(500);
            printf("Data: %s 3b\n", Message);
        } else if(strstr(Message, "four") != 0) {
            printf("Data: %s 4a\n", Message);
            Clear_Message();
            PAOUT = ~0x10;
            delay_ms(500);
            printf("Data: %s 4b\n", Message);
        } else {
            printf("%s", Message);
        }
        PAOUT = ~0x01; delay_ms(500);
        PAOUT = ~0x02; delay_ms(500);
        PAOUT = ~0x04; delay_ms(500);
        PAOUT = ~0x08; delay_ms(500);
    }
}

void delay_ms(unsigned int delay) {
    unsigned int x, y;
    for(x = 0; x <= delay; x++)
        for(y = 0; y <= 512; y++);
}

void Clear_Message(void) {
    int i;
    for(i = 0; i < MSG_LEN; i++)
        Message[i] = '\0';
    MessageIndex = 0;
}