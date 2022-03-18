#include "board.h"

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

void board_reset(t_cell (*board)[BOARD_SIZE]) {
    for (int r=0; r < BOARD_SIZE; r++) {
        for (int c=0; c < BOARD_SIZE; c++) {
            cell_default(&board[r][c]);
        }
    }
}

t_status board_check_bounds(t_pos *position)
{
    if (position->x >= BOARD_SIZE)
        return (OUTOFBOUNDS);
    if (position->y >= BOARD_SIZE)
        return (OUTOFBOUNDS);
    if (position->x < 0)
        return (OUTOFBOUNDS);
    if (position->y < 0)
        return (OUTOFBOUNDS);
    return (OKAY);
}

t_status board_check_range(t_pos *from, t_pos *to, int range)
{
    int x_diff;
    int y_diff;

    if (from->x > to->x)
        x_diff = from->x - to->x;
    else
        x_diff = to->x - from->x;
    if (from->y > to->y)
        y_diff = from->y - to->y;
    else
        y_diff = to->y - from->y;
    if (y_diff > range || x_diff > range)
        return (OUTOFRANGE);
    if (y_diff == 0 && x_diff == 0)
        return (INVALIDACTION);
    return (OKAY);
}

t_status board_check_isplayer(t_cell (*board)[BOARD_SIZE], t_pos *from)
{
    if (board[from->y][from->x].player > -1)
        return (OKAY);
    else
        return (INVALIDACTION);
}

t_status board_check_leveldiff(t_cell (*board)[BOARD_SIZE], t_pos *from, t_pos *to)
{
    int8_t to_level;
    int8_t from_level;

    to_level = board[to->y][to->x].level;
    from_level = board[from->y][from->x].level;
    if ((to_level - from_level) > 1)
        return (INVALIDACTION);
    return (OKAY);
}

t_status board_check_occupancy(t_cell (*board)[BOARD_SIZE], t_pos *pos)
{
    if (board[pos->y][pos->x].level == 4)
        return (DOMED);
    if (board[pos->y][pos->x].player > -1)
        return (OCCUPIED);
    return (OKAY);
}

void board_print(t_cell (*board)[BOARD_SIZE]) {
    for (int r=0; r < BOARD_SIZE; r++) {
        for (int c=0; c < BOARD_SIZE; c++) {
            char cc = 'E';
            if (board[r][c].player >= 0) {
                cc = board[r][c].player + 48;
            }
            if (board[r][c].level >= 4) {
                cc = 'D';
            }
            printf("%c%d ",cc,board[r][c].level);
        }
        printf("\n");
    }
};

t_status board_build_at(t_cell (*board)[BOARD_SIZE], t_pos *pos) {
	t_cell *cell = NULL;
    t_status ret = board_get_cell(board, pos, &cell);
    if (ret != OKAY) {
        return (ret);
    }
    if (cell_occupied(cell)) {
        return (OCCUPIED);
    }
    if (cell_domed(cell)) {
        return (DOMED);
    }
    cell_build(cell);
    return (OKAY);
}

/// Handles player movement actions
t_status board_player_move(t_cell (*board)[BOARD_SIZE], t_pos *from, t_pos *to, int8_t player) {
    // check if "from" and "to" are in bounds
    // check if "from" position == player
    // check if "to" is in range
    // check if "to".level - "from".level is at max 1
    // check if not occupied or domed -> "to".player < 0 && "to".level < 4
    // if true
    //      cell_set_empty(from)
    //      cell_set_player(to, player)
    //      check if "to".level == 3
    //          return WIN
    //      else
    //          return OKAY
    // else
    //      return SOMETHING
    return (OKAY);
}

/// Handles player buiding actions
/// Assumes range has been checked
t_status board_player_build(t_cell (*board)[BOARD_SIZE], t_pos *to) {
    // check if in bounds
    // check if not occupied / domed
    // if true
    //      cell_build(to)
    //      return OKAY
    // else
    //      return SOMEThING
	return OKAY;
}

/// returns number of neighbouring tiles to move to
int board_possible_moves_n(t_cell (*board)[BOARD_SIZE], t_pos *from) {
    return 0;
}

/// returns number of neighbouring tiles to build on
int board_possible_builds_n(t_cell (*board)[BOARD_SIZE], t_pos *from) {
    return 0;
}

/// check if win
int boar_check_win(t_cell (*board)[BOARD_SIZE]) {
    // iterates over the cells
    // if level==3 && occupied
    //  return cell.occupied
    // else
    //  return -1
	return -1;
}

t_status board_get_cell(t_cell (*board)[BOARD_SIZE], t_pos *pos, t_cell **cell) {
    t_status ret = position_bounds_check(pos, BOARD_SIZE);
    if (ret != OKAY) {
        return (ret);
    }
    *cell = &board[pos->y][pos->x];
    return (OKAY);
}

t_status board_place_player(t_cell (*board)[BOARD_SIZE], t_pos *pos, int8_t player) {
    t_cell *cell = NULL;
    t_status ret = board_get_cell(board, pos, &cell);
    if (ret != OKAY) {
        return (ret);
    }
    if (cell_occupied(cell)) {
        return (OCCUPIED);
    }
    cell_set_player(cell, player);
    return(OKAY);
}

t_status board_set_cell_empty(t_cell (*board)[BOARD_SIZE], t_pos *pos) {
	t_cell *cell = NULL;
    t_status ret = board_get_cell(board, pos, &cell);
    if (ret != OKAY) {
        return (ret);
    }
    cell_set_empty(cell);
    return(OKAY);
}