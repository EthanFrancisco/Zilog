#include <ez8.h>

#define sw1 (PBIN&0x01)
#define sw2 (PBIN&0x02)
#define sw3 (PBIN&0x04)
#define sw4 (PBIN&0x08)

void delay_ms(unsigned int delay);

void main() {
    unsigned int x;
	PADD = 0x00;
	PAAF = 0x00;
	PAOC = 0x00;
	PAHDE = 0xFF;
	
	PBDD |= 0x0F;
	PBAF &= 0xF0;
	
	while(1) {
		if((sw4 != 0) && (sw3 != 0) && (sw2 != 0) && (sw1 == 0)) {
			PAOUT = ~0x03;
		}
		else if((sw4 != 0) && (sw3 != 0) && (sw2 == 0) && (sw1 != 0)) {
			PAOUT = ~0x0C;
		}
		else if((sw4 != 0) && (sw3 != 0) && (sw2 == 0) && (sw1 == 0)) {
			PAOUT = ~0x0F;
		}
		else if((sw4 != 0) && (sw3 == 0) && (sw2 != 0) && (sw1 != 0)) {
			PAOUT = ~0x30;
		}
		else if((sw4 != 0) && (sw3 == 0) && (sw2 != 0) && (sw1 == 0)) {
			PAOUT = ~0x33;
		}
		else if((sw4 != 0) && (sw3 == 0) && (sw2 == 0) && (sw1 != 0)) {
			PAOUT = ~0x3C;
		}
		else if((sw4 != 0) && (sw3 == 0) && (sw2 == 0) && (sw1 == 0)) {
			PAOUT = ~0x3F;
		}
		else if((sw4 == 0) && (sw3 != 0) && (sw2 != 0) && (sw1 != 0)) {
			PAOUT = ~0xC0;
		}
		else if((sw4 == 0) && (sw3 != 0) && (sw2 != 0) && (sw1 == 0)) {
			PAOUT = ~0xC3;
		}
		else if((sw4 == 0) && (sw3 != 0) && (sw2 == 0) && (sw1 != 0)) {
			PAOUT = ~0xCC;
		}
		else if((sw4 == 0) && (sw3 != 0) && (sw2 == 0) && (sw1 == 0)) {
			PAOUT = ~0xCF;
		}
		else if((sw4 == 0) && (sw3 == 0) && (sw2 != 0) && (sw1 != 0)) {
			PAOUT = ~0xF0;
		}
		else if((sw4 == 0) && (sw3 == 0) && (sw2 != 0) && (sw1 == 0)) {
			PAOUT = ~0xF3;
		}
		else if((sw4 == 0) && (sw3 == 0) && (sw2 == 0) && (sw1 != 0)) {
			PAOUT = ~0xFC;
		}
		else if((sw4 == 0) && (sw3 == 0) && (sw2 == 0) && (sw1 == 0)) {
			PAOUT = ~0xFF;
		} else {
			PAOUT = ~0x80; delay_ms(200);
			PAOUT = ~0x40; delay_ms(200);
			PAOUT = ~0x20; delay_ms(200);
			PAOUT = ~0x10; delay_ms(200);
			PAOUT = ~0x08; delay_ms(200);
			PAOUT = ~0x04; delay_ms(200);
			PAOUT = ~0x02; delay_ms(200);
			PAOUT = ~0x01; delay_ms(200);
		}
	}
}

void delay_ms(unsigned int delay) {
	unsigned int x, y;
	for(x = 0; x <= delay; x++)
		for(y = 0; y <= 512; y++);
}