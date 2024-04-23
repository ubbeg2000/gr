#include <stdint.h>
#include <stdio.h>

#include "color.h"

uint8_t color_get_red(color_t color)
{
    return (color & 0xFF000000) >> 24;
}

uint8_t color_get_green(color_t color)
{
    return (color & 0x00FF0000) >> 16;
}

uint8_t color_get_blue(color_t color)
{
    return (color & 0x0000FF00) >> 8;
}

uint8_t color_get_alpha(color_t color)
{
    return (color & 0x000000FF);
}

uint8_t color_to_greyscale(color_t color)
{
    return (
        color_get_red(color) + 
        color_get_green(color) + 
        color_get_blue(color)
    ) / 3;
}

uint8_t color_to_ascii(ascii_bg bg, color_t color)
{
    uint32_t value = color_to_greyscale(color) * ASCII_CHARSET_MAX_VALUE >> 8;
    switch (bg)
    {
    case ASCII_LIGHT_BG:
        return ASCII_CHARSET[value];
        break;

    case ASCII_DARK_BG:
    default:
        return ASCII_CHARSET[ASCII_CHARSET_MAX_VALUE - value];
        break;
    }
}