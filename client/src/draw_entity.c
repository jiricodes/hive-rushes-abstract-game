#include "draw_entity.h"
#include "colors.h"

static int g_x_offset = 0;

void draw_cell_empty(int x, int y) {
    attron(COLOR_PAIR(2));
    attron(A_STANDOUT);
    for (int i=y; i < y + D_CELL_SIZE; i++) {
       for (int j=x; j < x + D_CELL_SIZE; j++) {
           mvaddch(i, j, ' ');
       } 
    }
    attroff(COLOR_PAIR(2));
    attroff(A_STANDOUT);
}

void draw_cell_level(int x, int y, uint8_t level) {
    attron(COLOR_PAIR(7));
    attron(A_STANDOUT);
    for (int i=y; i < y + D_CELL_SIZE; i++) {
       for (int j=x; j < x + D_CELL_SIZE; j++) {
           if (i < y + level || i >= y + D_CELL_SIZE - level || j < x + level || j >= x + D_CELL_SIZE - level) {
               mvaddch(i, j, ' ');
           }
       } 
    }
    attron(A_STANDOUT);
    attroff(COLOR_PAIR(7));
}

void draw_dome(int x, int y) {
	int limit = D_PLAYER_SIZE;
	y += 3;
	x += 3;
	attron(COLOR_PAIR(1));
    attron(A_STANDOUT);
	for (int i=y; i < y + limit; i++) {
       for (int j=x; j < x + limit; j++) {
           mvaddch(i, j, ' ');
       } 
    }
	attron(A_STANDOUT);
    attroff(COLOR_PAIR(1));
}

void draw_cell(int x, int y, uint8_t level) {
    if (level == 0) {
        draw_cell_empty(x, y);
    } else if (level <= 4) {
        draw_cell_level(x, y, level);
    	if (level == 4) {
			draw_dome(x, y);
		}
	}
}

void draw_player(int x, int y, uint8_t player) {
	y = y * D_CELL_SIZE + (y + 1) * D_MARGIN;
    x = x * D_CELL_SIZE + (x + 1) * D_MARGIN;
	y += D_CELL_SIZE / 2 - (D_PLAYER_SIZE) / 2;
	x += D_CELL_SIZE / 2 - (D_PLAYER_SIZE) / 2;
    x += g_x_offset;
	attron(C_PLAYER(player));
    attron(A_STANDOUT);
	for (int i=y; i < y + D_PLAYER_SIZE; i++) {
       for (int j=x; j < x + D_PLAYER_SIZE; j++) {
           mvaddch(i, j, ' ');
       } 
    }
	attron(A_STANDOUT);
    attroff(C_PLAYER(player));
}

void draw_check_x_offset() {
    int maxx = getmaxx(stdscr);
    int size = BOARD_SIZE * D_CELL_SIZE + (BOARD_SIZE + 1) * D_MARGIN;
    if (size < maxx) {
        g_x_offset = (maxx - size) / 2;
    }
}

void draw_board(t_cell (*board)[BOARD_SIZE]) {
    
    for (int y=0; y < BOARD_SIZE; y++) {
        for (int x=0; x < BOARD_SIZE; x++) {
            int cy = y * D_CELL_SIZE + (y + 1) * D_MARGIN;
            int cx = g_x_offset + x * D_CELL_SIZE + (x + 1) * D_MARGIN;
            draw_cell(cx, cy, board[y][x].level);
            if (board[y][x].player >= 0)
                draw_player(x, y, board[y][x].player);
        }
    }
}

void draw_player_cursor(int x, int y, uint8_t player) {
	x = g_x_offset + x * (D_CELL_SIZE + D_MARGIN);
	y = y * (D_CELL_SIZE + D_MARGIN);
    attron(C_PLAYER(player));
    attron(A_STANDOUT);
    int limit = D_CELL_SIZE + 2 * D_MARGIN;
    for (int i=y; i < y + limit; i++) {
       for (int j=x; j < x + limit; j++) {
           if (i < y + D_MARGIN || i >= y + limit - D_MARGIN || j < x + D_MARGIN || j >= x + limit - D_MARGIN) {
               mvaddch(i, j, ' ');
           }
       } 
    }
    attron(A_STANDOUT);
    attroff(C_PLAYER(player));
}


void draw_status_bar(char *player_info, char *stage_info, char *additional_info) {
    int maxx = getmaxx(stdscr);;
    int l = (strlen(player_info) + strlen(stage_info) + strlen(additional_info) + 6);
    int x = 0;
    if (l < maxx) {
        x = (maxx - l) / 2;
    }
    int y = BOARD_SIZE * D_CELL_SIZE + (BOARD_SIZE + 1) * D_MARGIN + 1;
    mvprintw(y, x, "%s | %s | %s", player_info, stage_info, additional_info);
}