#include <assert.h>
#include "board.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>

static void test_board() {
    printf("Testing Board:\n");
    t_cell      board[BOARD_SIZE][BOARD_SIZE];
    t_status    ret;
    t_cell      *cell = NULL;
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

static void get_player_str(uint8_t player, char *buffer) {
	sprintf(buffer, "PLAYER %d", player + 1);
}

static char **get_selected_str(t_pos *pos, char *buffer) {
    sprintf(buffer, "SELECTED { x: %d, y: %d }", pos->x, pos->y);
}

static void test_text_getters() {
    printf("Testing Text Getters:\n");
    t_game_controller game_controller;
	t_game_data game_data;

	game_controller_init(&game_controller);
	game_data_init(&game_data);
    game_controller.selected.x = 0;
    game_controller.selected.y = 0;
    char player_text[12];
    char stage_text[30];
    char select_text[30];
    get_player_str(game_controller.player, player_text);
    get_selected_str(&game_controller.selected, select_text);
    stage_as_str(game_controller.stage, stage_text);
    printf("%s | %s | %s\n", player_text, stage_text, select_text);
    printf("Done\n");
}

static void test_position() {
    t_pos buff[8] = {0};
    t_pos pos = {1, 1};
    position_neighbours(&pos, buff);
    for (int i = 0; i < 8; i++) {
        position_print(&buff[i]);
    }
}

int main() {
    printf("Starting Unittests\n");
    printf("DBG = %d\n", DBG_CONTROLS);
    test_board();
    // test_handle_init();
    // test_text_getters();
    test_position();
    printf("Tests done.\n");
    return (0);
}