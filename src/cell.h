#ifndef CELL_H
# define CELL_H

#include "status.h"
#include <inttypes.h>
#include "board_resources.h"

typedef struct s_cell {
    int8_t player; // -1 - empty, else N - player N
    int8_t level;
}               t_cell;

void cell_default(t_cell *cell);
void cell_build(t_cell *cell);
int cell_domed(t_cell *cell);
void cell_set_player(t_cell *cell, int8_t player);
void cell_set_empty(t_cell *cell);
int8_t cell_occupied(t_cell *cell);
t_status cell_can_build(t_cell *cell);

#endif