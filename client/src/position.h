#ifndef POSITION_H
#define POSITION_H

#include "status.h"
#include <stdio.h>
#include <inttypes.h>

#define POS_NONE 0xdeadbeef

typedef struct s_position {
    int x;
    int y;
} t_pos;


void position_zero(t_pos *position);
t_status position_bounds_check(t_pos *p, int size);
void position_print(t_pos *p);
void position_none(t_pos *pos);
int8_t position_is_none(t_pos *pos);
int position_toggle(t_pos *pos, t_pos *cursor);
#endif