/*
** snake.h
**
** Written by Peter Sutton
**
** Details of the snake
*/

/* Guard band to ensure this definition is only included once */
#ifndef SNAKE_H_
#define SNAKE_H_

#include <inttypes.h>
#include "position.h"

#define MAX_SNAKE_SIZE 32

/* Directions */
typedef enum {SNAKE_UP, SNAKE_RIGHT, SNAKE_DOWN, SNAKE_LEFT} SnakeDirnType;

/* Possible results of an attempt to move the snake */
#define OUT_OF_BOUNDS -1
#define COLLISION -2
#define SNAKE_LENGTH_ERROR -3
#define MOVE_OK 1
#define ATE_FOOD 2
#define ATE_FOOD_BUT_CANT_GROW 3

/* init_snake()
**
** Initialise the snake. 
*/
void init_snake(void);

/* get_snake_head_position()
**
** Returns the position of the head of the snake.
** (Should only be called after the snake is initialised.)
*/
PosnType get_snake_head_position(void);

/* get_snake_tail_position()
**
** Returns the position of the tail of the snake.
** (Should only be called after the snake is initialised.)
*/
PosnType get_snake_tail_position(void);

/* get_snake_length()
**
** Returns the current length of the snake.
** Normally this would be between 2 and MAX_SNAKE_SIZE inclusive
** but will become MAX_SNAKE_SIZE+1 if the snake length is MAX_SNAKE_SIZE
** and the head is advanced. In this case, the tail must also be advanced
** by one to ensure the length stays at MAX_SNAKE_SIZE.
** (Should only be called after the snake is initialised.)
*/
uint8_t get_snake_length(void);

/* advance_snake_head()
**
** Attempt to advance the snake's head by one in the 
** most recently set direction.
** Returns -1 (OUT_OF_BOUNDS) if the snake has run into the
** edge, -2 (COLLISION) if the snake has run into itself,
** -3 (SNAKE_LENGTH_ERROR) if the snake length is invalid,
** 1 (MOVE_OK) if the move is successful, 2 (ATE_FOOD)
** if the snake has eaten some food and can grow in size, 
** 3 (ATE_FOOD_BUT_CANT_GROW) if the snake has eaten some food
** but is already at the maximum length.
**
** This increases the snake's length by 1 also. The snake's
** tail must also be advanced to keep the snake length the
** same as it was before the head advanced.
*/
int8_t advance_snake_head();

/* advance_snake_tail()
**
** Move the snake's tail forward by one. (This reduces the 
** snake's length by 1.) This will always succeed provided
** it is called after a successful advanced of the head
** of the snake. It must not be called in any other 
** circumstances. The previous tail position is returned.
*/
PosnType advance_snake_tail();

/* set_snake_dirn(direction)
**
** Attempt to set snake direction.
** (Should be ignored if try and reverse snake - OK to continue
** in same direction or turn 90 degrees. Initial code will just
** accept any direction.) The direction
** will take effect when the snake head is moved. This
** function can be called multiple times - only the last
** value set before the snake is moved will be used.
*/
void set_snake_dirn(SnakeDirnType dirn);

/* is_snake_at(position)
**
** Returns 1 if the given position is occupied by 
** some part of the snake, 0 otherwise.
*/
int8_t is_snake_at(PosnType position);

#endif
