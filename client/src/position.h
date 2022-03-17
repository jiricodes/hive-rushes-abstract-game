#ifndef POSITION_H
#define POSITION_H

#include "status.h"
#include <stdio.h>

typedef struct s_position {
    int x;
    int y;
} t_pos;


void position_zero(t_pos *position);
t_status position_bounds_check(t_pos *p, int size);
void position_print(t_pos *p);

#endif