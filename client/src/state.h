#ifndef STATE_H
# define STATE_H
typedef enum e_game_stage {
	G_INIT,
	G_MOVE_SELECT,
	G_MOVE,
	G_BUILD,
	G_END
}			t_stage;
#endif