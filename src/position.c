#include "position.h"
void position_zero(t_pos *position) {
    position->x = 0;
    position->y = 0;
}

/// Checks bounds within 0..size
t_status position_bounds_check(t_pos *p, int size) {
    return OUTOFBOUNDS;
}

/// checks if abs values of  a - b are under range
t_status position_range_check(t_pos *a, t_pos *b, int range) {

}