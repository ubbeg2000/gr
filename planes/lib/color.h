#ifndef COLOR_H_
#define COLOR_H_

#include <stdint.h>

#define ASCII_CHARSET_LEN 71
#define ASCII_CHARSET_MAX_VALUE (ASCII_CHARSET_LEN - 1)
#define ASCII_CHARSET "$@B%%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. "

typedef uint32_t color_t;

typedef enum ascii_bg {
  ASCII_DARK_BG,
  ASCII_LIGHT_BG
} ascii_bg;

#define WHITE 0xFFFFFFFF
#define BLACK 0x000000FF
#define RED 0xFF0000FF
#define GREEN 0x00FF00FF
#define BLUE 0x0000FFFF
#define YELLOW 0xFFFF00FF
#define MAGENTA 0xFF00FFFF
#define CYAN 0x00FFFFFF

uint8_t color_get_red(color_t color);

uint8_t color_get_green(color_t color);

uint8_t color_get_blue(color_t color);

uint8_t color_get_alpha(color_t color);

uint8_t color_to_greyscale(color_t color);

uint8_t color_to_ascii(ascii_bg bg, color_t color);

#endif