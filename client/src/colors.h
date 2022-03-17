#ifndef COLORS_H
# define COLORS_H

# include <ncurses.h>

# define C_PLAYER(x) (x == 0 ? COLOR_PAIR(4): COLOR_PAIR(5))

int colors_init();

#endif