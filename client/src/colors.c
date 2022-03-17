# include "colors.h"
int colors_init() {
    use_default_colors();
    start_color();
    init_pair(1, COLOR_BLUE, -1);
    init_pair(2, COLOR_GREEN, -1);
    init_pair(3, COLOR_RED, -1);
    init_pair(4, COLOR_MAGENTA, -1);
    init_pair(5, COLOR_YELLOW, -1);
    init_pair(6, COLOR_CYAN, -1);
    init_pair(7, COLOR_WHITE, -1);
    init_pair(8, COLOR_MAGENTA, -1);
    return 0;
}