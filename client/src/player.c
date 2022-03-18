#include "player.h"

void player_reset(t_player *player) {
	for (int i = 0; i < WORKERS; i++) {
		position_none(&player->positions[i]);
	}
}

int player_place(t_player *player, t_pos *pos) {
	for (int i = 0; i < WORKERS; i++) {
		if (position_is_none(&player->positions[i])) {
			player->positions[i].x = pos->x;
			player->positions[i].y = pos->y;
			return (OKAY);
		}
	}
	return (INVALIDACTION);
}

int player_all_placed(t_player *player) {
	for (int i = 0; i < WORKERS; i++) {
		if (position_is_none(&player->positions[i])) {
			return (FREEWORKER);
		}
	}
	return (OKAY);
}

void player_print(t_player *player) {
	printf("Player {\n");
	for (int i = 0; i < WORKERS; i++) {
		printf("\t");
		position_print(&player->positions[i]);
	}
	printf("}\n");
}

int player_position_at(t_player *player, t_pos *pos) {
	for (int i = 0; i < WORKERS; i++) {
		if (player->positions[i].x == pos->x && player->positions[i].y == pos->y) {
			return (1);
		}
	}
	return (0);
}

t_status player_move_to(t_player *player, t_pos *from, t_pos *pos) {
	for (int i = 0; i < WORKERS; i++) {
		if (player->positions[i].x == from->x && player->positions[i].y == from->y) {
			player->positions[i].x = pos->x;
			player->positions[i].y = pos->y;
			return (OKAY);
		}
	}
	return (INVALIDACTION);
}