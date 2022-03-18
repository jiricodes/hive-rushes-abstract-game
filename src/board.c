#include "board.h"

/// holds available resources - L1 | L2 | l3 | DOME
static int8_t g_resources[4] = {0};

static void reset_resources() {
    g_resources[0] = 22;
    g_resources[1] = 18;
    g_resources[2] = 14;
    g_resources[3] = 18;
}

/// assumes `level` in range 0..4
static t_status get_resource(int8_t level) {
    if (g_resources[level] > 0) {
        g_resources[level] -= 1;
        return (OKAY);
    }
    return (NORESOURCE);
}


static int board_has_resource(int8_t level) {
    if (level < 0 || level > 3) {
        return (0);
    }
    return(g_resources[level] > 0);
}

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
    if (!board_has_resource(cell->level)) {
        return (NORESOURCE);
    }
    return (OKAY);
}

void board_reset(t_cell (*board)[BOARD_SIZE]) {
    reset_resources();
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
    int x_diff = abs(to->x - from->x);
    int y_diff = abs(to->y - from->y);

    if (y_diff > range || x_diff > range)
        return (OUTOFRANGE);
    if (y_diff == 0 && x_diff == 0)
        return (INVALIDACTION);
    return (OKAY);
}


t_status board_check_isplayer(t_cell (*board)[BOARD_SIZE], t_pos *pos, int8_t player)
{   
    t_cell *cell = NULL;
    t_status ret = board_get_cell(board, pos, &cell);
    if (ret != OKAY) {
        return (ret);
    }
    if (cell->player == player)
        return (OKAY);
    else
        return (INVALIDACTION);
}

t_status board_check_leveldiff(t_cell (*board)[BOARD_SIZE], t_pos *from, t_pos *to)
{
    t_cell *from_cell = NULL;
    t_cell *to_cell = NULL;

    t_status ret = board_get_cell(board, from, &from_cell);
    if (ret != OKAY) {
        return (ret);
    }
    ret = board_get_cell(board, to, &to_cell);
    if (ret != OKAY) {
        return (ret);
    }

    if ((to_cell->level - from_cell->level) > 1)
        return (INVALIDACTION);
    return (OKAY);
}

t_status board_check_occupancy(t_cell (*board)[BOARD_SIZE], t_pos *pos)
{
    t_cell *cell = NULL;
    t_status ret = board_get_cell(board, pos, &cell);
    if (ret != OKAY) {
        return (ret);
    }
    if (cell->level == 4)
        return (DOMED);
    if (cell->player > -1)
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
}

#if(DBG_CONTROLS == 1)
t_status board_debug_build_at(t_cell (*board)[BOARD_SIZE], t_pos *pos) {
	t_cell *cell = NULL;
    t_status ret = board_get_cell(board, pos, &cell);
    if (ret != OKAY) {
        return (ret);
    }
    if (cell_domed(cell)) {
        return (DOMED);
    }
    get_resource(cell->level);
    cell_build(cell);
    return (OKAY);
}
#endif

t_status board_player_in_range(t_cell (*board)[BOARD_SIZE], t_pos *from, int8_t player) {
    t_pos buff[8] = {0};
    position_neighbours(from, buff);

    t_status ret = OKAY;
    t_cell *cell = NULL;
    for (int i = 0; i < 8; i++) {
        ret = board_get_cell(board, &buff[i], &cell);
        if (ret == OKAY) {
            if (cell->player == player) {
                return (OKAY);
            }
        }
    }
    return (INVALIDACTION);
}

uint8_t board_count_possible_moves(t_cell (*board)[BOARD_SIZE], t_pos *from)
{
    t_pos buff[8] = {0};
    position_neighbours(from, buff);
    uint8_t moves = 0;

    t_status ret = OKAY;
    t_cell *cell = NULL;
    for (int i = 0; i < 8; i++)
    {
        ret = board_get_cell(board, &buff[i], &cell);
        if (ret == OKAY) {
            ret = board_check_occupancy(board, &buff[i]);
            if (ret == OKAY) {
                ret = board_check_leveldiff(board, from, &buff[i]);
                if (ret == OKAY) {
                    moves++;
                }
            }
        }
    }
    return (moves);
}

uint8_t board_count_possible_builds(t_cell (*board)[BOARD_SIZE], t_pos *from)
{
    t_pos buff[8] = {0};
    position_neighbours(from, buff);
    uint8_t builds = 0;

    t_status ret = OKAY;
    t_cell *cell = NULL;
    for (int i = 0; i < 8; i++)
    {
        ret = board_get_cell(board, &buff[i], &cell);
        // printf("get cell ret = %d\n", ret);
        if (ret == OKAY) {
            builds += !cell_can_build(cell);
            // printf("builds = %d\n", builds);
        }
    }
    return (builds);
}

/// Handles player movement actions
/// TODO: refactor
t_status board_player_move(t_cell (*board)[BOARD_SIZE], t_pos *from, t_pos *to, int8_t player) {
    // check if "from" and "to" are in bounds <- guaranteed by subsequent function
    t_cell *from_cell = NULL;
    t_status ret = board_get_cell(board, from, &from_cell);
    if (ret != OKAY) {
        return (ret);
    }
    t_cell *to_cell = NULL;
    ret = board_get_cell(board, to, &to_cell);
    if (ret != OKAY) {
        return (ret);
    }
    // check if "from" position == player
    ret =  board_check_isplayer(board, from, player);
    if (ret != OKAY) {
        return (ret);
    }

    // check if "to" is in range
    ret =  board_check_range(from, to, 1);
    if (ret != OKAY) {
        return (ret);
    }
    // check if "to".level - "from".level is at max 1
    ret =  board_check_leveldiff(board, from, to);
    if (ret != OKAY) {
        return (ret);
    }
    // check if not occupied or domed -> "to".player < 0 && "to".level < 4
    ret =  board_check_occupancy(board, to);
    if (ret != OKAY) {
        return (ret);
    }
    // remove player from current position
    cell_set_empty(from_cell);
    // add player to new position
    cell_set_player(to_cell, player);
    if (to_cell->level == 3) {
        return (VICTORY);
    }
    return (OKAY);
}

/// Handles player buiding actions
t_status board_player_build(t_cell (*board)[BOARD_SIZE], t_pos *from, t_pos *to, int8_t player) {
    // check if in bounds
    t_cell *cell = NULL;
    t_status ret = board_get_cell(board, to, &cell);
    if (ret != OKAY) {
        return (ret);
    }
    // check if from  in range to
    ret = board_check_range(from, to, 1);
    if (ret != OKAY) {
        return (ret);
    }
    // check if not occupied / domed
    if (cell_occupied(cell)) {
        return (OCCUPIED);
    }
    if (cell_domed(cell)) {
        return (DOMED);
    }
    // check if we have resources
    ret = get_resource(cell->level);
    if (ret != OKAY) {
        return (ret);
    }
    cell_build(cell);
    return (OKAY);
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
int board_check_win(t_cell (*board)[BOARD_SIZE]) {
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