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