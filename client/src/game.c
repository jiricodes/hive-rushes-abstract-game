#include "game.h"

void game_loop(t_cell (*board)[BOARD_SIZE]) {
    int ch = 0;
    while ((ch = getch())) {
        if (ch == KEY_EXIT) {
            break ;
        }
        clear();
        draw_board(board);
        refresh();
    }
}