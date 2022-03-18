#include "cell.h"

void cell_default(t_cell *cell) {
    cell->player = -1;
    cell->level = 0;
}

void cell_build(t_cell *cell) {
    cell->level += 1;
}

int cell_domed(t_cell *cell) {
	return (cell->level == 4);
}
void cell_set_player(t_cell *cell, int8_t player) {
    cell->player = player;
}

void cell_set_empty(t_cell *cell) {
    cell->player = -1;
}

int8_t cell_occupied(t_cell *cell) {
    return (cell->player >= 0);
}

t_status cell_can_build(t_cell *cell) {
    if (cell_occupied(cell)) {
        return (OCCUPIED);
    }
    if (cell_domed(cell)) {
        return (DOMED);
    }
    if (!resources_has_level(cell->level)) {
        return (NORESOURCE);
    }
    return (OKAY);
}
