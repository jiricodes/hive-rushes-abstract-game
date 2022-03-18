#include "position.h"
void position_zero(t_pos *position) {
    position->x = 0;
    position->y = 0;
}

void position_none(t_pos *pos) {
	pos->x = POS_NONE;
	pos->y = POS_NONE;
}

int8_t position_is_none(t_pos *pos) {
	return (pos->x == POS_NONE && pos->y == POS_NONE);
}

/// Helper function to handle pos assignment
/// assigns `from` values to `to`.
void position_assign(t_pos *to, t_pos *from) {
	to->x = from->x;
	to->y = from->y;
}

/// If pos is none, then cursor values are assigned
// if pos is cursor, then none values are assigned
// else nothing happens
// 1 - set, 0 - nothing, -1 - unset
int position_toggle(t_pos *pos, t_pos *cursor) {
	if (position_is_none(pos)) {
		pos->x = cursor->x;
		pos->y = cursor->y;
		return (1);
	} else if (pos->x == cursor->x && pos->y == cursor->y) {
		position_none(pos);
		return (-1);
	}
	return (0);
}

/// Checks bounds within 0..size
t_status position_bounds_check(t_pos *p, int size) {
    if (p->x < 0 || p->y < 0 || p->x >= size || p->y >= size)
        return (OUTOFBOUNDS);
    return (OKAY);
}

/// checks if abs values of  a - b are under range
t_status position_range_check(t_pos *a, t_pos *b, int range) {
	return OUTOFBOUNDS;
}

void position_print(t_pos *p) {
    printf("Pos {x: %d, y: %d}\n", p->x, p->y);
}

/// assumes buff is handled elsewhere
void position_neighbours(t_pos *pos, t_pos buff[8]) {
	// top left
	buff[0].x = pos->x - 1;
	buff[0].y = pos->y - 1;
	// top
	buff[1].x = pos->x;
	buff[1].y = pos->y - 1;
	// top right
	buff[2].x = pos->x + 1;
	buff[2].y = pos->y - 1;
	// left
	buff[3].x = pos->x - 1;
	buff[3].y = pos->y;
	// right
	buff[4].x = pos->x + 1;
	buff[4].y = pos->y;
	// bottom left
	buff[5].x = pos->x - 1;
	buff[5].y = pos->y + 1;
	// bottom
	buff[6].x = pos->x;
	buff[6].y = pos->y + 1;
	// bottom right
	buff[7].x = pos->x + 1;
	buff[7].y = pos->y + 1;
}