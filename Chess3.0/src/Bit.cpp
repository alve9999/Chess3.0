#include <cstdint>
#include "Bit.h"

//simple function that reverses any 8 bit integer
unsigned char reverse(unsigned char b) { 
	b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
	b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
	b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
	return b;
}

//counts the nummber of 1s in an 8bit nummber
int popCount8bit(uint8_t x) {
	int count = 0;
	while (x) {
		count++;
		x &= x - 1; // reset LS1B
	}
	return count;
}

//same as above except for 64 bit
int popCount64bit(uint64_t x) {
	int count = 0;
	while (x) {
		count++;
		x &= x - 1; // reset LS1B
	}
	return count;
}