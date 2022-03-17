# include "board.h"
# include <assert.h>

int main() {
    t_cell board[BOARD_SIZE][BOARD_SIZE];
    t_board_status ret;

    board_reset(board);
    board_print(board);
    printf("\nBuild at 1,1\n");
    ret = board_build_at(board, 1, 1);
    assert(ret == B_OK);
    board_print(board);
}