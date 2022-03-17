#include "board.h"

void cell_default(t_cell *cell) {
    cell->player = 0;
    cell->level = 0;
}

void cell_build(t_cell *cell) {
    cell->level += 1;
}

void cell_set_player(t_cell *cell, uint8_t player) {
    cell->player = player;
}

void cell_set_empty(t_cell *cell) {
    cell->player = 0;
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

t_board_status board_build_at(t_cell (*board)[BOARD_SIZE], uint8_t row, uint8_t col) {
    if (row >= BOARD_SIZE || col >= BOARD_SIZE) {
        return (B_OUTOFBOUNDS);
    }
    if (board[row][col].player) {
        return (B_OCCUPIED);
    }
    if (board[row][col].level == 4) {
        return (B_DOMED);
    }
    cell_build(&board[row][col]);
    return (B_OK);
}