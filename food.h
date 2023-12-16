/*
** food.h
**
** Written by Peter Sutton
**
** Function prototypes for those functions available externally
*/

/* Guard band to ensure this definition is only included once */
#ifndef FOOD_H_
#define FOOD_H_

#include <inttypes.h>
#include "position.h"


/* Maximum number of food items that can be on the board
** at any one time.
*/
#define MAX_FOOD 8

/* Each food item that is on the board will have an ID
** between 0 and MAX_FOOD-1 inclusive.
*/

/* init_food()
**
** Initialise the food details.
*/
void init_food(void); 

/* is_food_at(position)
**
** Returns true if there is a food item at the given position, 
** false (0) otherwise. The given position must be on the board.
*/
uint8_t is_food_at(PosnType posn);

/* food_at(position)
** 
** Returns -1 if there is no food at the given position,
** otherwise it returns the food ID of the food at that
** position. The ID is only valid until the next
** remove_food() operation (and can be used as the
** argument to the remove_food() operation).
** (The given position MUST be on the board.)
*/
int8_t food_at(PosnType posn);

/* add_food_item
**
** Add a food item to the game and return its position OR
** INVALID_POSITION if no food can be added (either the food array is
** full or no free space can be found on the board after a reasonable
** number of attempts).
*/
PosnType add_food_item(void);

/* get_position_of_food(foodID)
**
** Returns the position of the given food ID. foodID must be valid.
** If not, the return value is undefined.
*/
PosnType get_position_of_food(int8_t foodID);

/* remove_food(foodID)
**
** Remove a food item from our list of food. This could 
** change the IDs of other food items. The food item is
** removed from the display.
*/
void remove_food(int8_t foodID);

#endif
