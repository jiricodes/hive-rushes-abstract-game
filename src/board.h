#ifndef BOARD_H
# define BOARD_H

# include <stdio.h>
# include <stdlib.h>
# include <inttypes.h>

#include "status.h"
#include "position.h"
#include "debug.h"

# define BOARD_SIZE 5

typedef struct s_cell {
    int8_t player; // -1 - empty, else N - player N
    int8_t level;
}               t_cell;

void board_reset(t_cell (*board)[BOARD_SIZE]);
void board_print(t_cell (*board)[BOARD_SIZE]);

t_status board_player_build(t_cell (*board)[BOARD_SIZE], t_pos *from, t_pos *to, int8_t player);

t_status board_get_cell(t_cell (*board)[BOARD_SIZE], t_pos *pos, t_cell **cell);
t_status board_place_player(t_cell (*board)[BOARD_SIZE], t_pos *pos, int8_t player);
t_status board_set_cell_empty(t_cell (*board)[BOARD_SIZE], t_pos *pos);
t_status board_player_move(t_cell (*board)[BOARD_SIZE], t_pos *from, t_pos *to, int8_t player);

// Debug stuff
#if(DBG_CONTROLS == 1)
    t_status board_debug_build_at(t_cell (*board)[BOARD_SIZE], t_pos *pos);
#endif

#endif
