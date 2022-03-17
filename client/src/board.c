#include "board.h"

void cell_default(t_cell *cell) {
    cell->player = -1;
    cell->level = 0;
}

void cell_build(t_cell *cell) {
    cell->level += 1;
}

void cell_set_player(t_cell *cell, int8_t player) {
    cell->player = player;
}

void cell_set_empty(t_cell *cell) {
    cell->player = -1;
}

void board_reset(t_cell (*board)[BOARD_SIZE]) {
    for (int r=0; r < BOARD_SIZE; r++) {
        for (int c=0; c < BOARD_SIZE; c++) {
            cell_default(&board[r][c]);
        }
    }
}


void board_print(t_cell (*board)[BOARD_SIZE]) {
    for (int r=0; r < BOARD_SIZE; r++) {
        for (int c=0; c < BOARD_SIZE; c++) {
            char cc = 'E';
            if (board[r][c].player) {
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

t_status board_build_at(t_cell (*board)[BOARD_SIZE], uint8_t row, uint8_t col) {
    if (row >= BOARD_SIZE || col >= BOARD_SIZE) {
        return (OUTOFBOUNDS);
    }
    if (board[row][col].player >= 0) {
        return (OCCUPIED);
    }
    if (board[row][col].level == 4) {
        return (DOMED);
    }
    cell_build(&board[row][col]);
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
}