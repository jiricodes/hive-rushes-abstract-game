#include "draw.h"
#include <unistd.h>

static const char* g_splash_title[] = {
    "                                                                               ",
    " .d8888.  .d8b.  d8b   db d888888b  .d88b.  d8888b. d888888b d8b   db d888888b ",
    " 88'  YP d8' `8b 888o  88 `~~88~~' .8P  Y8. 88  `8D   `88'   888o  88   `88'   ",
    " `8bo.   88ooo88 88V8o 88    88    88    88 88oobY'    88    88V8o 88    88    ",
    "   `Y8b. 88~~~88 88 V8o88    88    88    88 88`8b      88    88 V8o88    88    ",
    " db   8D 88   88 88  V888    88    `8b  d8' 88 `88.   .88.   88  V888   .88.   ",
    " `8888Y' YP   YP VP   V8P    YP     `Y88P'  88   YD Y888888P VP   V8P Y888888P ",
    "                                                                               ",
    NULL
};

static const char *g_authors[] = {
    "           Created by            ",
    "  Jiri Novotny  (jiricodes.com)  ",
    "Lauri Salmi  (github.com/lasalmi)",
    NULL,
};

void draw_splash_title(int start_x, int start_y) {
    int x = start_x - 40;
    int y = start_y - 3;
    int row =0;
    attron(A_STANDOUT);
    while (g_splash_title[row]) {
        int col = 0;
        while (g_splash_title[row][col]) {
            attron(COLOR_PAIR(1));
            if (g_splash_title[row][col] == ' ') {
                attron(COLOR_PAIR(7));
            }
            mvaddch(y+row, x+col, ' ');
            col++;
        }
        row++;
    }
    attroff(A_STANDOUT);
    attroff(COLOR_PAIR(1));
}

void draw_authors(int start_x, int start_y) {
    int x = start_x - 17;
    int y = start_y - 1;
    int row = 0;
    while (g_authors[row]) {
        mvprintw(y + row, x, g_authors[row]);
        row++;
    }
}

void draw_any_key(int start_x, int start_y) {
    char s[] = "<PRESS ANY KEY TO CONTINUE>";
    int x = start_x - 14;
    mvprintw(start_y, x, s);
}

void draw_splash_screen() {
    clear();
    int y = getmaxy(stdscr) / 3;
    int x = getmaxx(stdscr) / 2;
    draw_splash_title(x, y);
    /// add little space
    y += 8;
    draw_authors(x, y);
    y += 8;
    int maxy = getmaxy(stdscr);
    if (y >= maxy) {
        y = maxy - 2;
    }
    draw_any_key(x, y);
    refresh();
    int ch = 0;
    while ((ch = getch())) {
        if (ch != -1) {
            break;
        }
    }
}