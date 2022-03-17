#ifndef GAME_H
# define GAME_H

#include <ncurses.h>
#include "draw.h"
#include "board.h"
#include "state.h"
#include "controller.h"

typedef struct s_game_controller {
	t_stage stage;
	t_pos	cursor;
	uint8_t player;
}					t_game_controller;

typedef struct s_game_data {
	t_cell	board[BOARD_SIZE][BOARD_SIZE];
}					t_game_data;

void game_loop();

#endif