#include <ez8.h>
void main() {
    unsigned int x;

    PADD = 0x00;
    PAAF = 0x00;
    PAOC = 0x00;
    PAHDE = 0xFF;

    while(1) {
        PAOUT = ~0x80; for(x = 0; x <= 0xffff; x++):
        PAOUT = ~0x40; for(x = 0; x <= 0xffff; x++):
        PAOUT = ~0x20; for(x = 0; x <= 0xffff; x++):
        PAOUT = ~0x10; for(x = 0; x <= 0xffff; x++):
        PAOUT = ~0x08; for(x = 0; x <= 0xffff; x++):
        PAOUT = ~0x04; for(x = 0; x <= 0xffff; x++):
        PAOUT = ~0x02; for(x = 0; x <= 0xffff; x++):
        PAOUT = ~0x01; for(x = 0; x <= 0xffff; x++):
    }
}