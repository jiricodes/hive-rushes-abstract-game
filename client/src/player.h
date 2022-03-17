#ifndef PLAYER_H
# define PLAYER_H

#include "position.h"
#include "status.h"

#define P_SLOTS 2
#define P_INIT_POS -69

typedef struct s_player {
    t_pos positions[P_SLOTS];
}   t_player;

void player_reset(t_player *player);
int player_place(t_player *player, t_pos *pos);
int player_all_placed(t_player *player);
void player_print(t_player *player);
int player_position_at(t_player *player, t_pos *pos);
t_status player_move_to(t_player *player, t_pos *from, t_pos *pos);
#endif