#ifndef _UI_H_
#define _UI_H_

#define MAXX 160
#define MAXY 50

#define MAX_INTENSITY 13
#define MIN_INTENSITY 4

#include <stdint.h>
#include <stdbool.h>
#include <locale.h>

typedef struct {
    uint32_t uint_value;
    int intensity;
} cell;

//extern - defined in matrix.c
extern cell matrix[MAXX][MAXY];

//prototypes
bool init_ui();
void cleanup_ui();
void show_matrix();
void sprintutf8(char * buffer, uint32_t code);

#endif
