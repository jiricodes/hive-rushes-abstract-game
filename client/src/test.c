#include <assert.h>
#include "board.h"
#include "game.h"
#include <stdio.h>

static void test_board() {
    printf("Testing Board:\n");
    t_cell      board[BOARD_SIZE][BOARD_SIZE];
    t_status    ret;
    t_cell      *cell = NULL;
    t_pos       pos;
    board_reset(board);
    position_zero(&pos);
    ret = board_get_cell(board, &pos, &cell);
    assert(ret == OKAY);
    fflush(stdout);
    assert(cell->level == 0 && cell->player == -1);
    ret = board_build_at(board, &pos);
    assert(ret == OKAY);
    assert(cell->level == 1 && cell->player == -1);
    ret = board_place_player(board, &pos, 1);
    assert(ret == OKAY);
    assert(cell->level == 1 && cell->player == 1);
    ret = board_place_player(board, &pos, 1);
    assert(ret == OCCUPIED);
    pos.x = -5;
    ret = board_place_player(board, &pos, 1);
    assert(ret == OUTOFBOUNDS);
    printf("Done\n");
}

static void test_handle_init() {
    printf("Testing Handle init:\n");
    t_game_controller game_controller;
	t_game_data game_data;

	game_controller_init(&game_controller);
	game_data_init(&game_data);
    player_print(&game_data.players[0]);
    player_print(&game_data.players[1]);
    handle_init(&game_controller, &game_data);
    game_controller.cursor.x = 1;
    handle_init(&game_controller, &game_data);
    player_print(&game_data.players[0]);
    game_controller.cursor.x = 2;
    handle_init(&game_controller, &game_data);
    game_controller.cursor.x = 3;
    handle_init(&game_controller, &game_data);
    player_print(&game_data.players[1]);
    board_print(game_data.board);
    printf("State: %d\n", game_controller.stage);
    fflush(stdout);
    printf("Done\n");
}

int main() {
    printf("Starting Unittests\n");
    test_board();
    test_handle_init();
    printf("Tests done.\n");
    return (0);
}