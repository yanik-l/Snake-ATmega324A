/*
 * score.c
 *
 * Written by Peter Sutton
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "score.h"
#include "stdio.h"
#include "terminalio.h"
#include "snake.h"

// Variable to keep track of the score. We declare it as static
// to ensure that it is only visible within this module - other
// modules should call the functions below to modify/access the
// variable.
static uint32_t score;
static uint32_t game_speed;

void init_score(void) {
	score = 0;
}

void add_to_score(uint16_t value) {
	score += value;
}

uint32_t get_score(void) {
	return score;
}

void print_score(void) {
	clear_terminal();
	printf("\rYour Score is:%10d", (int)get_score());
}

//Variables to set and manage the speed of the game
void initial_game_speed(void) {
	game_speed = 600;
}

uint32_t get_game_speed(void) {
	return game_speed;
}

//Takes away a set value from the game speed. It takes away since the game speed is 
//a time increment and a faster increment is a faster game
void change_game_speed(uint16_t value) {
	if(game_speed > 200) {
		game_speed -= value;
	}
}

/* Seven segment display digit being displayed.
** 0 = right digit; 1 = left digit.
*/
volatile uint8_t seven_seg_cc = 0;

/* Seven segment display segment values for 0 to 9 */
uint8_t seven_seg_data[10] = {63,6,91,79,102,109,125,7,127,111};
	
//Count for the length of the snake
static uint8_t SnakeLength;

void init_seven_seg_timer(void) {
	/* Make all bits of port C and the third
	** bit of port D be output bits.
	*/
	DDRC = 0xFF;
	DDRD |= (1<<DDRD2);
	
	/* Set up timer/counter 1 so that we get an 
	** interrupt 100 times per second, i.e. every
	** 10 milliseconds.
	*/
	OCR1A = 9999; /* Clock divided by 8 - count for 10000 cycles */
	TCCR1A = 0; /* CTC mode */
	TCCR1B = (1<<WGM12)|(1<<CS11); /* Divide clock by 8 */

	/* Enable interrupt on timer on output compare match 
	*/
	TIMSK1 = (1<<OCIE1A);

	/* Ensure interrupt flag is cleared */
	TIFR1 = (1<<OCF1A);
}

ISR(TIMER1_COMPA_vect) {
	/* Change which digit will be displayed. If last time was
	** left, now display right. If last time was right, now 
	** display left.
	*/
	seven_seg_cc = 1 ^ seven_seg_cc;
	
	//Checking to see how long the snake is and splitting this amount into tens and ones
	if(seven_seg_cc == 0) {
		/* Display rightmost digit - tenths of seconds */
		PORTC = seven_seg_data[get_length()%10];	
	}
	else {
		if(get_length() < 10) {
			PORTC = 0;
		} else {
			PORTC = seven_seg_data[((get_length()-get_length()%10)/10)];
		}

	}
	PORTD = (seven_seg_cc << 2);
}

void init_snake_length(void) {
	SnakeLength = 0;
}

uint8_t get_length(void) {
	return SnakeLength;
}

void add_to_length(uint8_t value) {
	SnakeLength += value;
}

