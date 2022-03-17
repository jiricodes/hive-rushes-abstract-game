# include "board.h"
# include <assert.h>
# include <ncurses.h>

# include "colors.h"
# include "game.h"

int main() {

    initscr();
    if (!has_colors()) {
        endwin();
        printf("Your terminal doesn't support color.\n");
        return 1;
    }

    // timeout(30);
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    colors_init();
    curs_set(0);

    game_loop();

    endwin();

    return 0;
}