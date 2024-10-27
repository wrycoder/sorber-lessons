#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include "ui.h"
#include <stdbool.h>

#define NUM_DRIPS 250

#define PROB_DRIP_SPAWN 0.65
#define PROB_DIM 0.55
#define PROB_CHANGE 0.95
// The traditional printable ASCII character set begins
// at \u0020 (the space character) and ends at \u007E
// (the tilde). The next printable character after that
// is \u00A0 (the non-breaking space).
// TODO: find an algorithm that skips the stuff between
// \u007E and \u00A0, but still allows for a few of those
// legacy characters to show up from time to time.
#define RANDOM_PRINTABLE_UNICODE_CHARACTER (unsigned int)(33 + (rand()%80))

typedef struct {
    int x, y;
    bool live;
    bool bright;
} drip;

cell matrix[MAXX][MAXY];
drip drips[NUM_DRIPS];



double rand01() {
    return (double)rand() / (double)RAND_MAX;
}

void init_drips() {
    for (int i=0; i < NUM_DRIPS; i++) {
        drips[i].live = false;
    }
}

void matrix_init() {
    //set the matrix all to black
    //move this later to matrix.c
    for (int x=0; x < MAXX; x++) {
        for (int y =0; y < MAXY; y++) {
            matrix[x][y].uint_value = (unsigned int)0;
            matrix[x][y].intensity = 0;
        }
    }

    //init drips
    init_drips();
}

void fade_n_change_matrix() {
    for (int x=0; x < MAXX; x++) {
        for (int y =0; y < MAXY; y++) {
            //randomly change characters --- even invisible ones.
            if (rand01() < PROB_CHANGE || matrix[x][y].char_value == 0) {
                matrix[x][y].char_value = RANDOM_PRINTABLE_CHARACTER;
            }
            //randomly dim the cells
            if (rand01() < PROB_DIM) {
                if (matrix[x][y].intensity > 0)
                    matrix[x][y].intensity--;    
            }
            
        }
    }
}

void try_add_drips() {
    for (int i=0; i < NUM_DRIPS; i++) {
        if (drips[i].live == false) {
            drips[i].live = true;
            drips[i].x = rand() % MAXX;
            drips[i].y = 0; 
            drips[i].bright = rand() % 2;
            return;
        }
    }
}

void update_drips() {
    for (int i=0; i < NUM_DRIPS; i++) {
        if (drips[i].live) {
            if (drips[i].bright) {
                matrix[drips[i].x][drips[i].y].intensity = MAX_INTENSITY;
            } else {
                matrix[drips[i].x][drips[i].y].intensity = MIN_INTENSITY;
            }
            //drips die when they leave the screen
            if (++drips[i].y >= MAXY-1) {
                drips[i].live = false;
            }
        }
    }
}

void matrix_update() {
    if (rand01() < PROB_DRIP_SPAWN) {
        try_add_drips();
    }
    update_drips();

    fade_n_change_matrix();
}