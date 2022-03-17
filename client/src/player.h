#ifndef PLAYER_H
# define PLAYER_H

#include "position.h"

typedef struct s_player {
    t_pos pos1;
    t_pos pos2;
}   t_player;

void player_reset(t_player *player);
#endif