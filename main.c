#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#define SMATH_IMPLEMENTATION
#include "smath.h"

#ifdef _WIN32
#define sleep(ms) Sleep(ms)
#endif

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32
#define SCREEN_SIZE SCREEN_WIDTH*SCREEN_HEIGHT
static uint8_t screen[SCREEN_SIZE];
#define ALIVE_CELL '0'
static size_t generation = 1;
static size_t population;

static void load_first_generation_from_file(const char *file_path)
{
    // 32 bytes for newline characters   
#define TMP_SIZE (SCREEN_SIZE + 32)
    uint8_t tmp[TMP_SIZE];
    
    FILE *fd = fopen(file_path, "rb");
    if (fd == NULL) {
	fprintf(stderr, "ERROR: could not load first generation from file\n");
	exit(-1);
    }

    fread(tmp, 1, TMP_SIZE, fd);
    fclose(fd);

    size_t cur = 0;
    for (size_t i = 0; i < TMP_SIZE; ++i) {
	switch (tmp[i]) {
	case '.':
	    screen[cur++] = ' ';
	    break;
	case '#':
	    screen[cur++] = ALIVE_CELL;
	    population += 1;
	    break;
	}
    }
}

static void render_screen(void)
{
    for (size_t row = 0; row < SCREEN_HEIGHT; ++row) {
	fwrite(&screen[row * SCREEN_WIDTH], 1, SCREEN_WIDTH, stdout);
	putc('\n', stdout);
    }

    printf("Generation: %zu\n", generation);
    printf("Population: %zu\n", population);

    // ANSI Escape codes
    printf("\x1b[%dD", SCREEN_WIDTH);
    printf("\x1b[%dA", SCREEN_HEIGHT+2);
}

static Vec2i index2vec(size_t index)
{
    Vec2i result;

    result.x = index % SCREEN_WIDTH; 
    result.y = index / SCREEN_WIDTH;

    return result;
}

static size_t vec2index(const Vec2i cell)
{
    return (size_t) ((cell.y * SCREEN_WIDTH) + cell.x);
}

static bool is_valid(Vec2i cell)
{
    if ((0 <= cell.x && cell.x < SCREEN_WIDTH ) &&
	(0 <= cell.y && cell.y < SCREEN_HEIGHT)) {
	return true;
    } else {
	return false;
    }
}

static bool is_alive(const size_t index)
{
    if (screen[index] == ALIVE_CELL)
	return true;
    else
	return false;
}

static int neighbours_count(const size_t index)
{
    int result = 0;
    
    Vec2i cell = index2vec(index);
    Vec2i neighbours[8] = {0};
    size_t cur = 0;

    for (int dy = -1; dy <= 1; ++dy) {
	for (int dx = -1; dx <= 1; ++dx) {
	    if ((dx == 0) && (dy == 0)) continue;

	    Vec2i d = vec2i(dx, dy);
	    Vec2i n = vec2i_add(cell, d);

	    if (is_valid(n)) neighbours[cur++] = n;
	}
    }

    for (size_t i = 0; i < cur; ++i) {
	Vec2i n = neighbours[i];

	if (is_alive(vec2index(n))) {
	    result += 1;
	}
    }

    return result;
}

static void next_generation(void)
{
    uint8_t tmp[SCREEN_SIZE] = {0};
    
    for (size_t i = 0; i < SCREEN_SIZE; ++i) {
	uint8_t cell = screen[i];
	int count = neighbours_count(i);

	switch (cell) {
	case ALIVE_CELL: {
	    if (count < 2 || count > 3) {
		tmp[i] = ' ';
		population -= 1;
	    } else {
		tmp[i] = ALIVE_CELL;
	    }
	} break;
	case ' ': {
	    if (count == 3) {
		tmp[i] = ALIVE_CELL;
		population += 1;
	    } else {
		tmp[i] = ' ';
	    }
	} break;
	}
    }

    memcpy(screen, tmp, SCREEN_SIZE);
    generation += 1;
}

#define FPS 15
int main(void)
{
    load_first_generation_from_file("first.map");

    while (true) {
	render_screen();
	next_generation();
	usleep(1000 * 1000 / FPS);
    }

    return 0;
}
