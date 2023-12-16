/*
 * score.h
 * 
 * Author: Peter Sutton
 */

#ifndef SCORE_H_
#define SCORE_H_

#include <stdint.h>

void init_score(void);
void add_to_score(uint16_t value);
uint32_t get_score(void);
void print_score(void);
void initial_game_speed(void);
uint32_t get_game_speed(void);
void change_game_speed(uint16_t value);
void init_seven_seg_timer(void);
void init_snake_length(void);
uint8_t get_length(void);
void add_to_length(uint8_t value);

#endif /* SCORE_H_ */