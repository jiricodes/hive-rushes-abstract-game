#include "game.h"
#include "assert.h"

void game_controller_init(t_game_controller *game_controller) {
	game_controller->stage = G_INIT;
	position_zero(&game_controller->cursor);
	game_controller->player = 0;
	position_none(&game_controller->selected);
	game_controller->last_status=OKAY;
}

void game_data_init(t_game_data *data) {
	board_reset(data->board);
	player_reset(&data->players[0]);
	player_reset(&data->players[1]);
}

static void get_player_str(uint8_t player, char *buffer) {
	sprintf(buffer, "PLAYER %d", player + 1);
}

t_status player_able_to_move(t_cell (*board)[BOARD_SIZE], t_player *player)
{
	uint8_t moves = 0;
	for (int i = 0; i < WORKERS; i++)
		moves += board_count_possible_moves(board, &player->positions[i]);
	if (moves)
		return (OKAY);
	return (LOSS);
}

t_status player_able_to_build(t_cell (*board)[BOARD_SIZE], t_pos *from)
{
	uint8_t builds = 0;
	builds += board_count_possible_builds(board, from);
	if (builds)
		return (OKAY);
	return (LOSS);
}

static char **get_selected_str(t_pos *pos, char *buffer) {
	if (!position_is_none(pos)) {
    	sprintf(buffer, "SELECTED { x: %d, y: %d }", pos->x, pos->y);
	}
}

void render(t_game_controller *game_controller, t_game_data *game_data) {
	clear();
	draw_check_x_offset();
	draw_board(game_data->board);
	draw_player_cursor(game_controller->cursor.x, game_controller->cursor.y, game_controller->player);
	char player_text[12] = {0};
    char stage_text[35] = {0};
    char select_text[30] = {0};
	get_player_str(game_controller->player, player_text);
    get_selected_str(&game_controller->selected, select_text);
    stage_as_str(game_controller->stage, stage_text);
	draw_status_bar( \
		player_text, \
		stage_text, \
		select_text\
	);

#if(DBG_CONTROLS == 1)
	draw_status_msg(game_controller->last_status);
#endif

    refresh();
}

void handle_init(t_game_controller *game_controller, t_game_data *game_data) {
	printf("Handle init\n");
	game_controller->last_status = board_place_player(game_data->board, &game_controller->cursor, game_controller->player);
	/// Couldnt place worker for some reason, repeat
	if (game_controller->last_status != OKAY) {
		return;
	}
	game_controller->last_status = player_place(&game_data->players[game_controller->player], &game_controller->cursor);
	if (game_controller->last_status != OKAY) {
		return;
	}
	game_controller->last_status = player_all_placed(&game_data->players[game_controller->player]);
	// If current player has free worker, continue placing
	if (game_controller->last_status == FREEWORKER) {
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
	game_controller->last_status = player_able_to_move(game_data->board, &game_data->players[game_controller->player]);
	if (game_controller->last_status == LOSS) {
		game_controller->stage = G_END;
		switch_player(&game_controller->player);
		return ;
	}

	if (player_position_at(&game_data->players[game_controller->player], &game_controller->cursor)) {
		int res = position_toggle(&game_controller->selected, &game_controller->cursor);
		if (res == 1) {
			game_controller->stage = G_MOVE;
		}
	} else {
		game_controller->last_status = INVALIDACTION;
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
	game_controller->last_status = board_player_move(\
		game_data->board, \
		&game_controller->selected, \
		&game_controller->cursor, \
		game_controller->player);
	if (game_controller->last_status != OKAY && game_controller->last_status != VICTORY) {
		return ;
	} else if (game_controller->last_status == VICTORY) {
		game_controller->stage = G_END;
	}
	game_controller->last_status = player_move_to(&game_data->players[game_controller->player], &game_controller->selected,&game_controller->cursor);
	assert(game_controller->last_status == OKAY);
	/// TODO: Add checking for game end!
	/// if end -> stage g_end
	/// Switch to build stage
	if (game_controller->stage != G_END) {
		game_controller->stage = G_BUILD;
	}
	/// Save cursor in selected, in order to use it as 'from' in build stage
	position_assign(&game_controller->selected, &game_controller->cursor);
	/// Check if we can even build from here
	game_controller->last_status = player_able_to_build(game_data->board, &game_controller->cursor);
	if (game_controller->last_status == LOSS) {
		game_controller->stage = G_END;
		switch_player(&game_controller->player);
		return ;
	}
}

void handle_build(t_game_controller *game_controller, t_game_data *game_data) {
	game_controller->last_status = board_player_build(game_data->board, &game_controller->selected, &game_controller->cursor, game_controller->player);
	if (game_controller->last_status == OKAY) {
		game_controller->stage = G_MOVE_SELECT;
		switch_player(&game_controller->player);
		/// clear selection
		position_none(&game_controller->selected);
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

int game_loop() {
	t_game_controller game_controller;
	t_game_data game_data;
	int ret = 0;

	game_controller_init(&game_controller);
	game_data_init(&game_data);

	render(&game_controller, &game_data);
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
			ret = -1;
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

			case ' ': {
				handle_select(&game_controller, &game_data);
				break;
			}
#if(DBG_CONTROLS == 1)
			case 'B':
			case 'b': {
				board_debug_build_at(game_data.board, &game_controller.cursor);
				break;
			}
#endif
			default:
				break;
		}
		// No need to do any updates if no user input
		if (ch != -1) {
			// Add check for win / loose
			render(&game_controller, &game_data);;
		}
		/// If we're in a game end stage, return to menu
		if (game_controller.stage == G_END) {
			ret = game_controller.player + 1;
			break;
		}
    }
	return (ret);
}