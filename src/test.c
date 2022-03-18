#include <assert.h>
#include "board.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>

static void test_board() {
    printf("Testing Board:\n");
    t_cell      board[BOARD_SIZE][BOARD_SIZE];
    // t_status    ret;
    // t_cell      *cell = NULL;
    t_pos       pos;
    board_reset(board);
    position_zero(&pos);
    int n = board_count_possible_builds(board, &pos);
    assert(n!=0);
    // ret = board_get_cell(board, &pos, &cell);
    // assert(ret == OKAY);
    // fflush(stdout);
    // assert(cell->level == 0 && cell->player == -1);
    // ret = board_build_at(board, &pos);
    // assert(ret == OKAY);
    // assert(cell->level == 1 && cell->player == -1);
    // ret = board_place_player(board, &pos, 1);
    // assert(ret == OKAY);
    // assert(cell->level == 1 && cell->player == 1);
    // ret = board_place_player(board, &pos, 1);
    // assert(ret == OCCUPIED);
    // pos.x = -5;
    // ret = board_place_player(board, &pos, 1);
    // assert(ret == OUTOFBOUNDS);
    printf("Done\n");
}

static void test_handle_init() {
    printf("Testing Handle init:\n");
    t_game_controller game_controller;
	t_game_data game_data;

	game_controller_init(&game_controller);
	game_data_init(&game_data);
    handle_init(&game_controller, &game_data);
	assert(game_data.players[0].positions[0].x == 0 && game_data.players[0].positions[0].y == 0);
    game_controller.cursor.x = 1;
    handle_init(&game_controller, &game_data);
    assert(game_data.players[0].positions[1].x == 1 && game_data.players[0].positions[1].y == 0);
    game_controller.cursor.x = 2;
    handle_init(&game_controller, &game_data);
	assert(game_data.players[1].positions[0].x == 2 && game_data.players[1].positions[0].y == 0);
    game_controller.cursor.x = 3;
    handle_init(&game_controller, &game_data);
    assert(game_data.players[1].positions[1].x == 3 && game_data.players[1].positions[1].y == 0);
    assert(G_MOVE_SELECT ==  game_controller.stage);
    fflush(stdout);
    printf("Done\n");
}


static void test_position() {
	printf("Testing positions:\n");
    t_pos buff[8] = {0};
    t_pos pos = {1, 1};
    position_neighbours(&pos, buff);
	assert(buff[0].x == 0 && buff[0].y == 0);
	assert(buff[1].x == 1 && buff[1].y == 0);
	assert(buff[2].x == 2 && buff[2].y == 0);
	assert(buff[3].x == 0 && buff[3].y == 1);
	assert(buff[4].x == 2 && buff[4].y == 1);
	assert(buff[5].x == 0 && buff[5].y == 2);
	assert(buff[6].x == 1 && buff[6].y == 2);
	assert(buff[7].x == 2 && buff[7].y == 2);
	printf("Done");
}

int main() {
    printf("Starting Unittests\n");
    printf("DBG = %d\n", DBG_CONTROLS);
    test_board();
    test_handle_init();
    test_position();
    printf("Tests done.\n");
    return (0);
}
