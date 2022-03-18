#include "game.h"
#include "assert.h"

void game_controller_init(t_game_controller *game_controller) {
	game_controller->stage = G_INIT;
	position_zero(&game_controller->cursor);
	game_controller->player = 0;
	position_none(&game_controller->selected);
}

void game_data_init(t_game_data *data) {
	board_reset(data->board);
	player_reset(&data->players[0]);
	player_reset(&data->players[1]);
}

void render(t_cell (*board)[BOARD_SIZE], t_pos *cursor, uint8_t player) {
	clear();
	draw_check_x_offset();
	draw_board(board);
	draw_player_cursor(cursor->x, cursor->y, player);
    refresh();
}

void handle_init(t_game_controller *game_controller, t_game_data *game_data) {
	t_status ret = OKAY;
	printf("Handle init\n");
	ret = board_place_player(game_data->board, &game_controller->cursor, game_controller->player);
	/// Couldnt place worker for some reason, repeat
	if (ret != OKAY) {
		printf("Couldn't place worker\n");
		return;
	}
	ret = player_place(&game_data->players[game_controller->player], &game_controller->cursor);
	if (ret != OKAY) {
		printf("Couldn't place player\n");
		return;
	}
	ret = player_all_placed(&game_data->players[game_controller->player]);
	// If current player has free worker, continue placing
	if (ret == FREEWORKER) {
		printf("Have free worker\n");
		return;
	}
	// Last player placed workers, move to next stage
	if (game_controller->player == MAX_PLAYERS - 1) {
		game_controller->stage = G_MOVE_SELECT;
	}
	// This works only with 2 players currently
	switch_player(&game_controller->player);
	return ;
}

void handle_move_select(t_game_controller *game_controller, t_game_data *game_data) {
	if (player_position_at(&game_data->players[game_controller->player], &game_controller->cursor)) {
		int res = position_toggle(&game_controller->selected, &game_controller->cursor);
		if (res == 1) {
			game_controller->stage = G_MOVE;
		}
	}
}

void handle_move(t_game_controller *game_controller, t_game_data *game_data) {
	if (player_position_at(&game_data->players[game_controller->player], &game_controller->cursor)) {
		int res = position_toggle(&game_controller->selected, &game_controller->cursor);
		if (res == -1) {
			game_controller->stage = G_MOVE_SELECT;
			return ;
		}
	}
	/// naive
	t_status ret = board_place_player(game_data->board, &game_controller->cursor, game_controller->player);
	if (ret != OKAY) {
		return ;
	}
	ret = board_set_cell_empty(game_data->board, &game_controller->selected);
	assert(ret == OKAY);
	ret = player_move_to(&game_data->players[game_controller->player], &game_controller->selected,&game_controller->cursor);
	assert(ret == OKAY);
	/// Switch to build stage
	game_controller->stage = G_BUILD;
	/// clear selection
	position_none(&game_controller->selected);
}

void handle_build(t_game_controller *game_controller, t_game_data *game_data) {
	t_status ret = board_build_at(game_data->board, &game_controller->cursor);
	if (ret == OKAY) {
		game_controller->stage = G_MOVE_SELECT;
		switch_player(&game_controller->player);
	}
}

void handle_select(t_game_controller *game_controller, t_game_data *game_data) {
	switch (game_controller->stage) {
		case G_INIT: {
			handle_init(game_controller, game_data);
			break;
		}
		case G_MOVE_SELECT: {
			//select player's worker to move
			handle_move_select(game_controller, game_data);
			break;
		}
		case G_MOVE: {
			handle_move(game_controller, game_data);
			break;
		}
		case G_BUILD: {
			handle_build(game_controller, game_data);
			break;
		}
		default: {
			printf("GAME END\n");
			break;
		}
	}
}

void game_loop() {
	t_game_controller game_controller;
	t_game_data game_data;

	game_controller_init(&game_controller);
	game_data_init(&game_data);

	render(game_data.board, &game_controller.cursor, game_controller.player);
    int ch = 0;
    while ((ch = getch())) {
		if (ch == 27 ) {
			int c = getch();
			if (c == -1)
				ch = KEY_EXIT;
		} else if (ch == 'q' || ch == 'Q') {
			ch = KEY_EXIT;
		}
        if (ch == KEY_EXIT) {
            break ;
        }
		switch (ch) {
			case KEY_LEFT: {
				cursor_left(&game_controller.cursor);
				break;
			}

			case KEY_RIGHT: {
				cursor_right(&game_controller.cursor);
				break;
			}

			case KEY_UP: {
				cursor_up(&game_controller.cursor);
				break;
			}

			case KEY_DOWN: {
				cursor_down(&game_controller.cursor);
				break;
			}

			case 'p':
			case 'P': {
				switch_player(&game_controller.player);
				break;
			}

			case ' ': {
				handle_select(&game_controller, &game_data);
				break;
			}
 
			default:
				break;
		}
		// No need to do any updates if no user input
		if (ch != -1) {
			// Add check for win / loose
			render(game_data.board, &game_controller.cursor, game_controller.player);
		}
    }
}