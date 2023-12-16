/*
** position.h
**
** Written by Peter Sutton
**
** 
*/

/* Guard band to ensure this definition is only included once */
#ifndef POSITION_H_
#define POSITION_H_

#include <inttypes.h>

/* The type that we use for positions. This is an 8 bit type - the
** upper 4 bits holds the x value (column number = 0 on the left, 15 on the right),
** the lower 4 bits holds the y value (0 on the bottom, 7 on the top). */
typedef uint8_t PosnType;

/* Any position value that has a y value (lower 4 bits) 8 to 15 
** (i.e. bit 3 is set is considered invalid). We define a constant
** we can use if need to set/define an invalid position but note
** that other positions are invalid - use the is_position_valid()
** function to check for validity if required.
*/ 
#define INVALID_POSITION (0x08)

/* Functions that can extract the x and y values from a position type */
uint8_t x_position(PosnType posn);
uint8_t y_position(PosnType posn);

/* Function to check if position is valid or not. Returns true if OK
** false (0) otherwise. */
int8_t is_position_valid(PosnType posn);

/* Function to construct a position from x and y values.
** The x value used will be the lower 4 bits (i.e. the number
** will be in the range 0 to 15. The y value used will be lower
** 3 bits (i.e. the number will be in the range 0 to 7. A valid
** position will result.
*/
PosnType position(uint8_t x, uint8_t y);

#endif
