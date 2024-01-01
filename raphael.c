#ifndef __RAPHAEL
#define __RAPHAEL

#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>

void swap_int(int *a, int *b) {

    int t = *a;
    *a = *b;
    *b = t;
}

void raphael_draw(uint32_t *pixels, size_t width, size_t height, uint32_t color) {

    for (size_t i = 0; i < width*height; ++i) {
        pixels[i] = color;
    }
}

void raphael_draw_rect(
    uint32_t *pixels,
    size_t pWidth, size_t pHeight,
    int x0, int y0,
    size_t w, size_t h,
    uint32_t color) {

    for (int dy = 0; dy < (int)h; ++dy) {
        int y = y0 + dy;
        if (0 <= y && y < (int)pHeight) {
            for (int dx = 0; dx < (int)w; ++dx) {
                int x = x0 + dx;
                if (0 <= x && x < (int)pWidth) {
                    pixels[y*pWidth+x] = color;
                }
            }
        }
    }
}

void raphael_draw_circle(
    uint32_t *pixels,
    size_t pWidth, size_t pHeight,
    int cx, int cy,
    size_t r,
    uint32_t color) {

    int x1 = cx - r;
    int x2 = cx + r;
    int y1 = cy - r;
    int y2 = cy + r;
    for (int y = y1; y <= y2; ++y) {
        if (0 <= y && y < (int)pHeight) {
            for (int x = x1; x <= x2; ++x) {
                
                int dx = x - cx;
                int dy = y - cy;
                if (dx*dx + dy*dy <= r*r) {

                    pixels[y*pWidth+x] = color;
                }
            }
        }
    }
}

void raphael_draw_chess(uint32_t *pixels, size_t width, size_t height,
                size_t cols, size_t rows,
                uint32_t color1, uint32_t color2) {
    size_t cell_width = (width/cols);
    size_t cell_height= (height/rows);
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            uint32_t color ;
            if ((x+y)%2 == 0) {
                color = color1;
            }else {
                color = color2;
            }
            raphael_draw_rect(pixels, width, height, x*cell_width, y*cell_height, cell_width, cell_height, color);
        }
    }
}

void raphael_draw_line( uint32_t *pixels,
                        size_t width, size_t height,
                        int x1, int x2, int y1, int y2,
                        uint32_t color) {

    int dx = x2 - x1;
    int dy = y2 - y1;

    if (dx != 0) {
        int k = dy/dx;
        int c = y1 -k*x1;

        if (x1 > x2) swap_int(&x1, &x2);
        for (int x = x1; x <= x2; ++x) {
        if (0 <= x && x < (int)width) {
            int y = x*k + c;
            if (0 <= y && y < (int)height) {
                pixels[y*width+x] = color;
            }
        }}
    }else {
        int x = x1;
        if (0 <= x && x < (int)width) {
            if (y1 > y2) swap_int(&y1, &y2);
            for (int y = y1; y <= y2; ++y) {
            if (0 <= y && y < (int)height) {
                pixels[y*width+x] = color;
            }}
        }
    }
}

void raphael_draw_sprite(  uint32_t *pixels,
                    size_t pWidth, size_t pHeight,
                    int posX,   int posY,
                    int width,  int height,
                    uint32_t shape[width][height]) {

    for (int dy = 0; dy < (int)height; ++dy) {
        int y = posY + dy;
        if (0 <= y && y < (int)pHeight) {
            for (int dx = 0; dx < (int)width; ++dx) {
                int x = posX + dx;
                if (0 <= x && x < (int)pWidth) {
                    pixels[x+y*pWidth] = shape[dy][dx];
                }
            }
        }
    }
}

typedef int Errno;

#define return_defer(value) do { result = (value); goto defer; } while (0)

Errno raphael_save_to_ppm_file(uint32_t *pixels, size_t width, size_t height, const char *file_path) {

    int result = 0;
    FILE *f = NULL;

    {
        f = fopen(file_path, "wb");
        if (f == NULL) return_defer(errno);

        fprintf(f, "P6\n%zu %zu 255\n", width, height);

        if (ferror(f)) return_defer(errno);

        for (size_t i = 0; i < width*height; ++i) {
            // 0xAABBGGRR
            uint32_t pixel = pixels[i];
            __uint8_t bytes[3] = {
                (pixel>>8*0)&0xFF,
                (pixel>>8*1)&0xFF,
                (pixel>>8*2)&0xFF,
            };
            fwrite(bytes, sizeof(bytes), 1, f);
            if (ferror(f)) return_defer(errno);
        }
    }

defer:
    if (f) fclose(f);
    return result;
}

#endif // RAPHAEL