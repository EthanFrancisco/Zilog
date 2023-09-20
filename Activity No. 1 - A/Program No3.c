/*
    a. set the first and fifth bits of the input to logic 1 and then
    b. set the second, third and sixth bits to logic 0 and then
    c. toggle the second and fourth bits and then
    d. shift to the left by 4 positions and then
    e. shift to the right by 5 positions
    And display on monitor the result for each operation.
*/

#include <ez8.h>
#include <stdio.h>

#define sw1 (PBIN & 0x01)
#define sw2 (PBIN & 0x02)
#define sw3 (PBIN & 0x04)
#define sw4 (PBIN & 0x08)

void delay(unsigned int ms);
int POUT = 0x00;

void main() {
    PBDD = 0x0F;
    PBAF = 0x00;
    while(1) {
		if((sw1 != 0) || (sw2 != 0) || (sw3 != 0) || (sw4 != 0)) {
			  POUT |= 0x11; 	  printf("Hex: %02X\n", POUT);  delay(1000);
			  POUT &= 0x26; 	  printf("Hex: %02X\n", POUT);  delay(1000);
			  POUT ^= 0x0A; 	  printf("Hex: %02X\n", POUT);  delay(1000);
			  POUT = POUT << 4;   printf("Hex: %02X\n", POUT);  delay(1000);
			  POUT = POUT >> 5;   printf("Hex: %02X\n", POUT);  delay(1000);
		  }
    }
}

void delay(unsigned int ms) {
    unsigned int x, y;
    for(x = 0; x <= ms; x++)
        for(y = 0; y <= 512; y++);
}