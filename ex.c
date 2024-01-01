#include "raphael.c"
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>

#define WIDTH 480
#define HEIGHT 300

#define COLS 48
#define ROWS 30
#define CELL_WIDTH  (WIDTH/COLS)
#define CELL_HEIGHT (HEIGHT/ROWS)

#define BACKGROUND_COLOR 0xFF2D0010

static uint32_t pixels[WIDTH*HEIGHT];

int main(void) {

    raphael_draw(pixels, WIDTH, HEIGHT, BACKGROUND_COLOR);

    /*
    raphael_fill_chess(pixels, WIDTH, HEIGHT, COLS, ROWS, BACKGROUND_COLOR, 0xFFDF69FF);
    raphael_fill_circle(pixels, WIDTH, HEIGHT, WIDTH/2, HEIGHT/2, 100, 0xFFDF69FF);
    */

    uint32_t sprChar[8][8] = {
        {0xFFDF69FF, 0xFFDF69FF, 0xFFDF69FF, 0xFFDF69FF, 0xFFDF69FF, 0xFFDF69FF, 0xFFDF69FF, 0xFFDF69FF},
        {0x00000000, 0xFFDF69FF, 0x00000000, 0x00000000, 0xFFDF69FF, 0x00000000, 0xFFDF69FF, 0xFFDF69FF},
        {0x00000000, 0xFFDF69FF, 0x00000000, 0x00000000, 0xFFDF69FF, 0x00000000, 0xFFDF69FF, 0xFFDF69FF},
        {0x00000000, 0xFFFF005F, 0xFFFF005F, 0xFFFF005F, 0x00000000, 0x00000000, 0xFFDF69FF, 0xFFDF69FF},
        {0xFFDF69FF, 0xFFDF69FF, 0xFFDF69FF, 0xFFFF005F, 0x00000000, 0xFFDF69FF, 0xFFDF69FF, 0x00000000},
        {0xFFDF69FF, 0xFFDF69FF, 0x00000000, 0xFFFF005F, 0xFFDF69FF, 0xFFDF69FF, 0x00000000, 0x00000000},
        {0xFFDF69FF, 0x00000000, 0x00000000, 0x00000000, 0xFFDF69FF, 0x00000000, 0x00000000, 0x00000000},
        {0xFFDF69FF, 0x00000000, 0x00000000, 0x00000000, 0xFFDF69FF, 0x00000000, 0x00000000, 0x00000000}
    };

    raphael_draw_sprite(pixels, WIDTH, HEIGHT, 100, 100, 8, 8, sprChar);
    raphael_draw_line(pixels, WIDTH, HEIGHT, 0, 0, WIDTH, HEIGHT, 0xFFFFFFFF);

    const char *file_path = "out/output.ppm";
    Errno err = raphael_save_to_ppm_file(pixels, WIDTH, HEIGHT, file_path);
    if (err) {
        fprintf(stderr, "ERROR: Cound not save file %s: %s\n", file_path, strerror(errno));
        return 1;
    }
    return 0;
}