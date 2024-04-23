#ifndef RASTER_H_
#define RASTER_H_

#include <stdint.h>

#include "object.h"

typedef struct canvas_t 
{
    color_t *content;
    uint32_t width, height, size;
    double depth;
} canvas_t;

typedef struct coordinate_t
{
    int32_t x, y;
} coordinate_t;

canvas_t* new_canvas(uint32_t width, uint32_t height, double depth);

coordinate_t* point_orthogonal_projection(canvas_t *canvas, point_t *p);

coordinate_t* point_perspective_projection(canvas_t *canvas, point_t *p, double z_value);

void rasterize_surfaces(canvas_t *canvas, object_t *object, double z_value);

void rasterize_points(canvas_t *canvas, object_t *object, double z_value);

void clear_canvas(canvas_t *canvas);

int set_canvas_value(canvas_t *canvas, coordinate_t *c, color_t value);

int draw_triangle(canvas_t *canvas, coordinate_t *a, coordinate_t *b, coordinate_t *c, color_t fill);

void print_canvas(canvas_t *canvas, ascii_bg bg);

#endif