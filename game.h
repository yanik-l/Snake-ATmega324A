/*
 * game.h
 *
 * Written by Peter Sutton
 */ 

#ifndef GAME_H_
#define GAME_H_

#include <inttypes.h>
#include "position.h"

// Initialise game. This initialises the board with snake and food items
// and initialises the display.
void init_game(void);

// Attempt to move snake forward. If food is eaten it removes it, grows
// the snake if possible and replaces the food item with a new one.
// Display is updated as required. Returns true if successful, 
// false otherwise (move off board if not permitted, or snake collides
// with self). (Moves off board and collisions permitted in initially 
// supplied code.)
int8_t attempt_to_move_snake_forward(void);

void spawn_superfood(void);

#endif /* GAME_H_ */