#ifndef CONTROLLER_H
# define CONTROLLER_H

#include "board.h"
#include "position.h"

void cursor_left(t_pos *cursor);
void cursor_right(t_pos *cursor);
void cursor_up(t_pos *cursor);
void cursor_down(t_pos *cursor);
void switch_player(uint8_t *player);

#endif
