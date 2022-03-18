# include <ncurses.h>

# include "colors.h"
# include "game.h"

int main() {

    // Ncureses init
    initscr();
    if (!has_colors()) {
        endwin();
        printf("Your terminal doesn't support color.\n");
        return (1);
    }

    timeout(1);
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    // Init colors
    colors_init();
    curs_set(0);

    /// Multi handler
    /// 0 - nothing significant, keep running
    /// -1 - user wants to exit
    /// 1+ - id of victorions player
    int game_ret = 0;

    while (game_ret >= 0) {
        // Draw splash
        game_ret = draw_splash_screen(game_ret);
        if (game_ret == -1) {
            break;
        }
        // Enter game loop
        game_ret = game_loop();
    }

    // Cleanup
    endwin();

    return (0);
}