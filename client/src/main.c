# include <ncurses.h>

# include "colors.h"
# include "game.h"

int main() {

    // Ncureses init
    initscr();
    if (!has_colors()) {
        endwin();
        printf("Your terminal doesn't support color.\n");
        return 1;
    }

    timeout(1);
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    // Init colors
    colors_init();
    curs_set(0);

    // Draw splash
    draw_splash_screen();
    // Enter game loop
    game_loop();

    // Cleanup
    endwin();

    return 0;
}