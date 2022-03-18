#ifndef DRAW_ENTITY_H
# define DRAW_ENTITY_H

# include <ncurses.h>
# include <stdlib.h>
# include <string.h>

# include "board.h"

# define D_CELL_SIZE 8
# define D_MARGIN 1
# define D_PLAYER_SIZE D_CELL_SIZE-6

void draw_cell(int x, int y, uint8_t level);
void draw_board(t_cell (*board)[BOARD_SIZE]);
void draw_player_cursor(int x, int y, uint8_t player);
void draw_player(int x, int y, uint8_t player);
void draw_check_x_offset();
void draw_status_bar(char *player_info, char *stage_info, char *additional_info);

#endif