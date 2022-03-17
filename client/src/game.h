#ifndef GAME_H
# define GAME_H

#include <ncurses.h>
#include "draw.h"
#include "board.h"

void game_loop(t_cell (*board)[BOARD_SIZE]) ;

#endif