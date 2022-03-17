#include "player.h"

void player_reset(t_player *player) {
	for (int i = 0; i < P_SLOTS; i++) {
		player->positions[i].x = P_INIT_POS;
		player->positions[i].y = P_INIT_POS;
	}
}

int player_place(t_player *player, t_pos *pos) {
	for (int i = 0; i < P_SLOTS; i++) {
		if (player->positions[i].x == P_INIT_POS && player->positions[i].y == P_INIT_POS) {
			player->positions[i].x = pos->x;
			player->positions[i].y = pos->y;
			return (OKAY);
		}
	}
	return (INVALIDACTION);
}

int player_all_placed(t_player *player) {
	for (int i = 0; i < P_SLOTS; i++) {
		if (player->positions[i].x == P_INIT_POS && player->positions[i].y == P_INIT_POS) {
			return (FREEWORKER);
		}
	}
	return (OKAY);
}

void player_print(t_player *player) {
	printf("Player {\n");
	for (int i = 0; i < P_SLOTS; i++) {
		printf("\t");
		position_print(&player->positions[i]);
	}
	printf("}\n");
}