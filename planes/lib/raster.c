#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "raster.h"
#include "object.h"

#define MIN(A, B) (A < B ? A : B)
#define MAX(A, B) (A > B ? A : B)

canvas_t* new_canvas(uint32_t width, uint32_t height, double depth)
{
    canvas_t *ret = calloc(1, sizeof(canvas_t));
    ret->depth = depth;
    ret->width = width;
    ret->height = height;
    ret->size = width * height;
    ret->content = calloc(ret->size, sizeof(color_t));
    return ret;
}

int is_coordinate_outside_bounds(coordinate_t *coord, uint32_t x_bound, uint32_t y_bound)
{
    return coord->x < 0 || coord->x >= x_bound || coord->y < 0 || coord->y >= y_bound;
}

coordinate_t* point_orthogonal_projection(canvas_t *canvas, point_t *p)
{
    if (p->z < canvas->depth) return NULL;

    coordinate_t *ret = calloc(1, sizeof(coordinate_t));

    ret->x = p->x;
    ret->y = p->y;

    return ret;
}

coordinate_t* point_perspective_projection(canvas_t *canvas, point_t *p, double z_value)
{
    if (p->z < canvas->depth || p->z - canvas->depth + z_value == 0) return NULL;

    coordinate_t *ret = calloc(1, sizeof(coordinate_t));
    
    double v = (canvas->depth - p->z) / (p->z - canvas->depth + z_value);
    
    ret->x = p->x * (v + 1);
    ret->y = p->y * (v + 1);

    return ret;
}

coordinate_t* normalize_coordinate(canvas_t *canvas, coordinate_t *coord)
{
    coordinate_t *ret = calloc(1, sizeof(coordinate_t));
    ret->x = coord->x + canvas->width / 2;
    ret->y = coord->y + canvas->height / 2;
    if (is_coordinate_outside_bounds(ret, canvas->width, canvas->height)) 
    {
        free(ret);
        return NULL;
    }
    return ret;
}

int set_canvas_value(canvas_t *canvas, coordinate_t *c, color_t value)
{
    coordinate_t *cn = normalize_coordinate(canvas, c);
    if (cn == NULL) return -1;
    
    uint32_t idx = cn->y * canvas->width + cn->x;
    free(cn);

    if (idx > canvas->size) return -1;
    
    canvas->content[idx] = value;
    return 0;
}

double triangle_area(coordinate_t *a, coordinate_t *b, coordinate_t *c)
{
   return fabs((a->x*(b->y-c->y) + b->x*(c->y-a->y)+ c->x*(a->y-b->y))/2.0);
}

int is_point_inside_triangle(coordinate_t *a, coordinate_t *b, coordinate_t *c, coordinate_t *p)
{
    double area = triangle_area(a, b, c);
    double area1 = triangle_area(p, b, c);
    double area2 = triangle_area(a, p, c);
    double area3 = triangle_area(a, b, p);
    
    return area == area1 + area2 + area3 ? 1 : 0;
}

int draw_triangle(canvas_t *canvas, coordinate_t *a, coordinate_t *b, coordinate_t *c, color_t fill)
{
    if (a == NULL || b == NULL ||c == NULL) return -1;

    int32_t min_x = MIN(a->x, MIN(b->x, c->x));
    int32_t min_y = MIN(a->y, MIN(b->y, c->y));
    int32_t max_x = MAX(a->x, MAX(b->x, c->x));
    int32_t max_y = MAX(a->y, MAX(b->y, c->y));

    for (int32_t i = min_y; i <= max_y; i++) {
        for (int32_t j = min_x; j <= max_x; j++) {
            coordinate_t p = {.x = j, .y = i};

            if (!is_point_inside_triangle(a, b, c, &p)) continue;

            set_canvas_value(canvas, &p, fill);
        }
    }

    return 0;
}

void rasterize_surfaces(canvas_t *canvas, object_t *object, double z_value)
{
    surface_t *surface;
    coordinate_t *a, *b, *c;
    coordinate_t *a_norm, *b_norm, *c_norm;
    double *z_buffer;

    z_buffer = calloc(canvas->size, sizeof(double));
    for (int i = 0; i < canvas->size; i++) z_buffer[i] = INFINITY;
    
    for (int i = 0; i < object->surfaces_len; i++)
    {
        surface = object->surfaces[i];
        if (surface->points_len != 3) continue;

        a = point_perspective_projection(canvas, surface->points[0], z_value);
        b = point_perspective_projection(canvas, surface->points[1], z_value);
        c = point_perspective_projection(canvas, surface->points[2], z_value);

        if (a == NULL || b == NULL ||c == NULL) return;

        int32_t min_x = MIN(a->x, MIN(b->x, c->x));
        int32_t min_y = MIN(a->y, MIN(b->y, c->y));
        int32_t max_x = MAX(a->x, MAX(b->x, c->x));
        int32_t max_y = MAX(a->y, MAX(b->y, c->y));

        for (int32_t j = min_y; j <= max_y; j++) {
            for (int32_t k = min_x; k <= max_x; k++) {
                coordinate_t p = { .x = k, .y = j };

                if (is_point_inside_triangle(a, b, c, &p) == 0) continue;

                vector_t *r = new_vector(
                    surface->points[2]->x - surface->points[0]->x,
                    surface->points[2]->y - surface->points[0]->y,
                    surface->points[2]->z - surface->points[0]->z
                );
                vector_t *s = new_vector(
                    surface->points[1]->x - surface->points[0]->x,
                    surface->points[1]->y - surface->points[0]->y,
                    surface->points[1]->z - surface->points[0]->z
                );
                vector_t *normal = vector_cross_product(r, s);

                double z_distance = 
                    surface->points[0]->z - (
                        normal->x * (p.x - surface->points[0]->x) + 
                        normal->y * (p.y - surface->points[0]->y)
                    ) / normal->z;

                free(r);
                free(s);
                free(normal);

                coordinate_t *norm_p = normalize_coordinate(canvas, &p);
                if (norm_p == NULL) continue;

                if (z_buffer[norm_p->y * canvas->height + norm_p->x] < z_distance) {
                    free(norm_p);
                    continue;
                }

                z_buffer[norm_p->y * canvas->height + norm_p->x] = z_distance;
                set_canvas_value(canvas, &p, surface->color);

                free(norm_p);
            }
        }
    }

    free(a);
    free(b);
    free(c);
}

void rasterize_points(canvas_t *canvas, object_t *object, double z_value)
{
    surface_t *surface;
    double *z_buffer;

    z_buffer = calloc(canvas->size, sizeof(double));
    for (int i = 0; i < canvas->size; i++) z_buffer[i] = INFINITY;
    
    for (int i = 0; i < object->surfaces_len; i++)
    {
        surface = object->surfaces[i];
        for (int j = 0; j < surface->points_len; j++)
        {
            coordinate_t *c = point_perspective_projection(canvas, surface->points[j], z_value);
            coordinate_t *norm_c = normalize_coordinate(canvas, c);

            if (z_buffer[norm_c->y * canvas->height + norm_c->x] < surface->points[j]->z) 
            {
                free(c);
                free(norm_c);
                continue;
            }
            
            z_buffer[norm_c->y * canvas->height + norm_c->x] = surface->points[j]->z;
            set_canvas_value(canvas, c, surface->color);

            free(c);
            free(norm_c);
        }   
    }
}

void clear_canvas(canvas_t *canvas)
{
    for (size_t i = 0; i < canvas->size; i++) canvas->content[i] = color_to_greyscale(0);
}

void print_canvas(canvas_t *canvas, ascii_bg bg)
{
    size_t buffer_size = canvas->size + canvas->height + 1;
    char buffer[buffer_size];
    memset(buffer, color_to_ascii(bg, 0), buffer_size * sizeof(char));
    buffer[buffer_size - 1] = '\0';
    
    for (uint32_t y = 0; y < canvas->height; y++)
    {
        for (uint32_t x = 0; x < canvas->width; x++)
        {
            uint32_t idx = y * canvas->width + x;
            buffer[idx + y] = color_to_ascii(bg, canvas->content[idx]);
        }
        buffer[y * canvas->width + canvas->width + y] = '\n';
    }
    puts(buffer);
}