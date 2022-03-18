#ifndef BOARD_RESOURCES_H
# define BOARD_RESOURCES_H

#include "status.h"
#include "inttypes.h"

void reset_resources();
t_status resources_get_one(int8_t level);
int resources_has_level(int8_t level);
int8_t reseources_get_n(int8_t level);

#endif