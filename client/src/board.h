#ifndef BOARD_H
# define BOARD_H

# include <stdio.h>
# include <stdlib.h>
# include <inttypes.h>

# define BOARD_SIZE 5

typedef enum e_board_status {
    B_OK,
    B_OUTOFBOUNDS,
    B_OCCUPIED,
    B_DOMED
}   t_board_status;

typedef struct s_cell {
    uint8_t player;
    uint8_t level;
}               t_cell;

void board_reset(t_cell (*board)[BOARD_SIZE]);
void board_print(t_cell (*board)[BOARD_SIZE]);
t_board_status board_build_at(t_cell (*board)[BOARD_SIZE], uint8_t row, uint8_t col);

#endif