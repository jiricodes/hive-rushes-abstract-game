#include "game.h"

void game_controller_init(t_game_controller *game_controller) {
	game_controller->stage = G_INIT;
	position_zero(&game_controller->cursor);
	game_controller->player = 0;
}

void game_data_init(t_game_data *data) {
	board_reset(data->board);
	player_reset(&data->players[0]);
	player_reset(&data->players[1]);
}

void render(t_cell (*board)[BOARD_SIZE], t_pos *cursor, uint8_t player) {
	clear();
	draw_board(board);
	draw_player_cursor(cursor->x, cursor->y, player);
    refresh();
}

void handle_select(t_game_controller *game_controller, t_game_data *game_data) {
	switch (game_controller->stage) {
		case G_INIT: {
			// place player
			break;
		}
		case G_MOVE: {
			//move pleayer
			break;
		}
		case G_BUILD: {
			//build
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

			}
 
			default:
				break;
		}
		// Add check for win / loose
        render(game_data.board, &game_controller.cursor, game_controller.player);
    }
}