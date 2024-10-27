
#include "ui.h"
#include <string.h>
#include <assert.h>
#include <curses.h>
#include <unistd.h>

WINDOW *uiwindow = NULL;

int color_map[MAX_INTENSITY+1] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 4, 5, 3, 6};

void set_colors();

bool init_ui() {
    
    // get the locale
    setlocale(LC_ALL, "");
    //init curses
    uiwindow = initscr();
    if (uiwindow == NULL) return false;

    start_color();
    if (!has_colors() || !can_change_color() || COLOR_PAIRS < 6) {
        printf("Warning. Your terminal can't handle this program.\n");
        return false;
    }

    set_colors();

    return true;
}

void cleanup_ui() {
    delwin(uiwindow);
    endwin();
    refresh();
}

void show_matrix() {
    char displaychars[4];
    for (int x=0; x < MAXX; x++) {
        for (int y =0; y < MAXY; y++) {
            int intensity = matrix[x][y].intensity;
            color_set(color_map[intensity], NULL);
            sprintutf8(displaychars, matrix[x][y].uint_value);
            mvaddstr(y, x, displaychars);
        }
    }
    refresh();
}

void set_colors() {
    for (int i=0; i < 8; i++) {
        init_pair(i+1, i, COLOR_BLACK);
    }
    //set shades of green
    for (int i=0; i <= 5; i++) {
        init_color(i, 0, i*200, 0);
    }
    init_color(6, 800, 1000, 800);
}