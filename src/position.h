#ifndef POSITION_H
#define POSITION_H

#include "status.h"

typedef struct s_position {
    int x;
    int y;
} t_pos;


void position_zero(t_pos *position);

#endif