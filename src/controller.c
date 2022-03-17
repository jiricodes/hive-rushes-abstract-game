#include "controller.h"

void cursor_left(t_pos *cursor) {
	if (cursor->x > 0) {
		cursor->x -= 1;
	}
}

void cursor_right(t_pos *cursor) {
	if (cursor->x < BOARD_SIZE - 1) {
		cursor->x += 1;
	}
}

void cursor_up(t_pos *cursor) {
	if (cursor->y > 0) {
		cursor->y -= 1;
	}
}

void cursor_down(t_pos *cursor) {
	if (cursor->y < BOARD_SIZE - 1) {
		cursor->y += 1;
	}
}

void switch_player(uint8_t *player) {
	*player = !*player;
}