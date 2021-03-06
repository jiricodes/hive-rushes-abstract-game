#ifndef DRAW_H
# define DRAW_H

#include "draw_entity.h"
#include "colors.h"

typedef struct s_draw_dimensions {
    int width;
    int height;
}               t_draw_dim;


int draw_splash_screen();
void draw_digit(int x, int y, int digit);

#endif
