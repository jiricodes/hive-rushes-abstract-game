#ifndef DRAW_ENTITY_H
# define DRAW_ENTITY_H

# include <ncurses.h>

# include "board.h"

# define D_CELL_SIZE 8
# define D_MARGIN 1

void draw_cell(int x, int y, uint8_t level);
void draw_board(t_cell (*board)[BOARD_SIZE]);
void draw_player_cursor(int x, int y, uint8_t player);

#endif