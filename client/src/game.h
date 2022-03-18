#ifndef GAME_H
# define GAME_H

#include <ncurses.h>
#include "draw.h"
#include "board.h"
#include "state.h"
#include "controller.h"
#include "position.h"
#include "player.h"
#include <stdio.h>

#define MAX_PLAYERS 2

typedef struct s_game_controller {
	t_stage stage;
	t_pos	cursor;
	t_pos	selected;
	uint8_t player;
}					t_game_controller;

typedef struct s_game_data {
	t_cell	board[BOARD_SIZE][BOARD_SIZE];
	t_player players[MAX_PLAYERS];
}					t_game_data;

int game_loop();
void game_controller_init(t_game_controller *game_controller);
void game_data_init(t_game_data *data);
void handle_init(t_game_controller *game_controller, t_game_data *game_data);
uint8_t board_count_possible_moves(t_cell (*board)[BOARD_SIZE], t_pos *from);
uint8_t board_count_possible_builds(t_cell (*board)[BOARD_SIZE], t_pos *from);
#endif