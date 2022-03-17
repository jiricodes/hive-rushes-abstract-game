#ifndef BOARD_H
# define BOARD_H

# include <stdio.h>
# include <stdlib.h>
# include <inttypes.h>

#include "status.h"
#include "position.h"

# define BOARD_SIZE 5

typedef struct s_cell {
    int8_t player; // -1 - empty, else N - player N
    int8_t level;
}               t_cell;

void board_reset(t_cell (*board)[BOARD_SIZE]);
void board_print(t_cell (*board)[BOARD_SIZE]);
t_status board_build_at(t_cell (*board)[BOARD_SIZE], uint8_t row, uint8_t col);
t_status board_get_cell(t_cell (*board)[BOARD_SIZE], t_pos *pos, t_cell **cell);
t_status board_place_player(t_cell (*board)[BOARD_SIZE], t_pos *pos, int8_t player);

#endif