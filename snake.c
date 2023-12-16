/*
** snake.c
**
** Written by Peter Sutton
**
** Details of the snake and making it move.
*/

#include "position.h"
#include "snake.h"
#include "board.h"
#include "food.h"
#include "score.h"

#define SNAKE_POSITION_ARRAY_SIZE ((MAX_SNAKE_SIZE)+1)

/* Global variables.
** These are static so can't be accessed outside this file - they
** can only be accessed via functions in this file.
*/
/* snakePositions
**
** We store the snake in a circular buffer - an array which can 
** wrap around from the end to the start. The array is of size
** MAX_SNAKE_SIZE+1. This allows the head to advance by 1 without
** overwriting the tail position.
*/
static PosnType snakePositions[SNAKE_POSITION_ARRAY_SIZE];

/* snakeLength
**
** Variable to keep track of the length of the snake.
** This should be between 2 and MAX_SNAKE_SIZE inclusive, but
** will become MAX_SNAKE_SIZE+1 if the snake is at maximum size
** and the head is advanced. If this is the case, the tail must
** be advanced to restore the length to MAX_SNAKE_SIZE.
*/
static uint8_t snakeLength;

/* snakeHeadIndex and snakeTailIndex
**
** Positions (array indexes) in the array of where we can find 
** the head and tail positions of the snake.
** If the snake hasn't wrapped around, the head position is at a higher
** index in the array, e.g. where T represents the tail and H represents the
** head and array index 0 is on the left:
**    ---TSSSSSSH--------------------- (tail index 3, head index 10, length 8)
** If the snake has wrapped around, the head position is at a lower index
** in the array, e.g.
**    SSSH-------------------------TSSS (tail index 29, head index 3, length 8)
**
**
** (The index values are in the range of 0 to MAX_SNAKE_SIZE inclusive.)
*/
static int8_t snakeHeadIndex;
static int8_t snakeTailIndex;

/* curSnakeDirn and nextSnakeDirn
** 
** Variables to keep track of the current direction 
** of the snake and the proposed next direction of
** the snake. The "next direction" will take effect
** when the snake is moved.
*/
static SnakeDirnType curSnakeDirn;
static SnakeDirnType nextSnakeDirn;

/* FUNCTIONS */
/* init_snake()
**
** Resets our snake to the initial configuration
*/
void init_snake(void) {
	/* Snake starts at (1,1) and finishes at (2,1) and
	** has an initial length of 2. These positions will
	** be stored at indexes 0 and 1 in the array. Snake 
	** is initially moving to the right.
	*/
	snakeLength = 2;
	snakeTailIndex = 0;
	snakeHeadIndex = 1;
	snakePositions[0] = position(1,1);
	snakePositions[1] = position(2,1);
	curSnakeDirn = SNAKE_RIGHT;
    nextSnakeDirn = SNAKE_RIGHT;
}

/* get_snake_head_position()
**
** Returns the position of the head of the snake. 
*/
PosnType get_snake_head_position(void) {
    return snakePositions[snakeHeadIndex];
}

/* get_snake_tail_position()
**
** Returns the position of the tail of the snake.
*/
PosnType get_snake_tail_position(void) {
	return snakePositions[snakeTailIndex];
}

/* get_snake_length()
**
** Returns the length of the snake.
*/
uint8_t get_snake_length(void) {
	return snakeLength;
}

/* advance_snake_head()
**
** Attempt to move snake head forward. Returns
** - OUT_OF_BOUNDS if snake has run into the edge and wrap-around is not permitted
**   (in the initial code, wrap-around happens by default) and this value is never returned
** - COLLISION if snake would run into itself
**	 (in the initial code, this is not checked for)
** - SNAKE_LENGTH_ERROR if snake is already too long
** - MOVE_OK if the snake head moves forward but no food was there
** - ATE_FOOD if there was food at the new head position and the snake can grow
** - ATE_FOOD_BUT_CANT_GROW if there was food at the new head position but the
**   snake can't grow.
** (Only the last three of these result in the head position being moved.)
*/
int8_t advance_snake_head(void) {
	int8_t headX;	/* head X position */
	int8_t headY;	/* head Y position */
	PosnType newHeadPosn;
	
	/* Check the snake isn't already too long */
	if(snakeLength > MAX_SNAKE_SIZE) {
		return SNAKE_LENGTH_ERROR;
	}
    
	/* Current head position */
	headX = x_position(snakePositions[snakeHeadIndex]);
	headY = y_position(snakePositions[snakeHeadIndex]);
    
    /* Work out where the new head position should be - we
    ** move 1 position in our NEXT direction of movement if we can.
	** If we're at the edge of the board, then we wrap around to
	** the other edge.
    */
    switch (nextSnakeDirn) {
        case SNAKE_UP:
			if(headY == BOARD_HEIGHT - 1) {
				// Head is already at the top of the board - wrap around
				headY = 0;
			} else {
	            headY += 1;
			}
            break;
		case SNAKE_DOWN:
			if(headY == 0) {
				// Head is already at the bottom of the board - wrap around
				headY = BOARD_HEIGHT - 1;
			} else {
				headY -= 1;
			}
			break;
        case SNAKE_RIGHT:
			if(headX == BOARD_WIDTH - 1) {
				// Snake head is already at the right hand edge of the board
				// - wrap around to left hand side
				headX = 0;
			} else {
				headX += 1;
			}
            break;
        case SNAKE_LEFT:
        if(headX == 0) {
	        // Snake head is already at the left hand edge of the board
	        // - wrap around to right hand side
	        headX = BOARD_WIDTH - 1;
	        } else {
	        headX -= 1;
        }
        break;			
		/* YOUR CODE HERE to deal with other directions */
    }

	newHeadPosn = position(headX, headY);

	/* Update the current direction */
	curSnakeDirn = nextSnakeDirn;

	/* ADD CODE HERE to check whether the new head position
	** is already occupied by the snake (other than the tail), and if so, return
	** COLLISION. Do not continue. See snake.h for a function which can help you.
	** (If the new head position is the same as the current tail position then
	** this move is permitted - the tail position won't be updated until after the
	** head is advanced but we don't consider this a collision.
	*/
	
	if(is_snake_at(newHeadPosn) == 1) {
		if(newHeadPosn == get_snake_tail_position()) {
		} else{
			return COLLISION;
		}
	}

    /*
    ** If we get here, the move should be possible.
    ** Advance head by 1. First work out the index
	** of the new head position in the array of snake positions.
	** and whether this has wrapped around in our array of positions
	** or not. Update the length.
    */
	snakeHeadIndex++;
	if(snakeHeadIndex == SNAKE_POSITION_ARRAY_SIZE) {
		/* Array has wrapped around */
		snakeHeadIndex = 0;
	}
	/* Store the head position */
	snakePositions[snakeHeadIndex] = newHeadPosn;
	/* Update the snake's length */
	snakeLength++;
	
	/* Check whether we ate food or not and return the appropriate
	** value.
	*/
	if(is_food_at(newHeadPosn)) {
		if(snakeLength <= MAX_SNAKE_SIZE) {
			add_to_score(3);
			return ATE_FOOD;
		} else {
			add_to_score(3);
			return ATE_FOOD_BUT_CANT_GROW;
		}
	} else {
		add_to_score(1);
		return MOVE_OK;
	}
}

/* 
** advance_snake_tail() 
**
** Attempt to move the snake's tail forward by 1. This
** should always succeed provided it followed a successful
** advance of the head. (We don't check this.) We decrement
** the snake length (to match the increment when the head
** was advanced.)
** No positions need to be updated, we just let the last tail
** position "drop" off the end.
** We return the previous tail position.
*/
PosnType advance_snake_tail(void) {
	// Get the current tail position
	PosnType prev_tail_position = snakePositions[snakeTailIndex];
	
	/* Update the tail index */
	snakeTailIndex++;
	if(snakeTailIndex == SNAKE_POSITION_ARRAY_SIZE) {
		/* Array has wrapped around */
		snakeTailIndex = 0;
	}
	snakeLength--;
	
	return prev_tail_position;
}

/* set_snake_dirn
**      Attempt to set the next snake direction.
**      (Should be ignored if try and reverse snake from its current
**      direction, but otherwise the direction will be accepted.)
**      It's OK to continue in same direction or turn 90 degrees.
*/
void set_snake_dirn(SnakeDirnType dirn) {
	/* YOUR CODE HERE - MODIFY THIS FUNCTION */
	/* You must write code to check that the proposed direction (dirn)
	** is not opposite to the current direction (stored in curSnakeDirn). 
	**
	** Initially, we assume the move is OK and just set the 
	** next direction.
	*/
	if(curSnakeDirn == SNAKE_RIGHT && dirn == SNAKE_LEFT) {
		nextSnakeDirn = curSnakeDirn;
	} else if(curSnakeDirn == SNAKE_LEFT && dirn == SNAKE_RIGHT) {
		nextSnakeDirn = curSnakeDirn;
	} else if(curSnakeDirn == SNAKE_UP && dirn == SNAKE_DOWN) {
		nextSnakeDirn = curSnakeDirn;
	} else if(curSnakeDirn == SNAKE_DOWN && dirn == SNAKE_UP) {
		nextSnakeDirn = curSnakeDirn;
	} else{
		nextSnakeDirn = dirn;
	}
}

/* is_snake_at
**		Check all snake positions and see if any part of the 
**		snake is at the given position
*/
int8_t is_snake_at(PosnType position) {
	int8_t index;

	/* Start at tail and work forward to the head.
	*/
	index = snakeTailIndex;
	while(index != snakeHeadIndex) {
		if(position == snakePositions[index]) {
			return 1;
		}
		index++;
		if(index > MAX_SNAKE_SIZE) {
			index = 0;
		}
	}
	/* Now check head position, since it is not checked above. */
	if(position == snakePositions[snakeHeadIndex]) {
		return 1;
	}
	/* Snake does not occupy the given position */
	return 0;
}
		
