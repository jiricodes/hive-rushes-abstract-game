#ifndef PLAYER_H
# define PLAYER_H

#include <inttypes.h>

#include "position.h"
#include "status.h"

#define WORKERS 2

typedef struct s_player {
    t_pos positions[WORKERS];
}   t_player;

void player_reset(t_player *player);
int player_place(t_player *player, t_pos *pos);
int player_all_placed(t_player *player);
void player_print(t_player *player);
int player_position_at(t_player *player, t_pos *pos);
t_status player_move_to(t_player *player, t_pos *from, t_pos *pos);
#endif
