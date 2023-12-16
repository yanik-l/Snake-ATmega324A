/*
** position.c
**
** Written by Peter Sutton
**
*/

#include "position.h"

/* Functions that can extract the x and y values from a position type 
*/
uint8_t x_position(PosnType posn) {
	return (posn >> 4) & 0x0F;
}

uint8_t y_position(PosnType posn) {
	return (posn & 0x0F);
}

int8_t is_position_valid(PosnType posn) {
	// We extract bit 3 of the position. If this is 0, then the 
	// position is valid (otherwise the y position is 8 or higher)
	return ((posn & 0x08) == 0);
}

/* Function to construct a position from x and y values.
** We  take the lower 4 bits of the x value and the lower
** 3 bits of the y value.
*/
PosnType position(uint8_t x, uint8_t y) {
	return ((x & 0x0F) << 4) | (y & 0x07);
}
