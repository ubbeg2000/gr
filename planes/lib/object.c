#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>

#include "object.h"

object_t* new_object(int surfaces_len, ...) 
{
    object_t *ret = calloc(1, sizeof(object_t));

    va_list valist;
 
    va_start(valist, surfaces_len);

    ret->surfaces_len = surfaces_len;
    ret->surfaces = calloc(surfaces_len, sizeof(surface_t*));


    for (int i = 0; i < surfaces_len; i++) 
    {
        surface_t *surface = (surface_t*)va_arg(valist, void*);
        ret->surfaces[i] = surface;
    }
 
    va_end(valist);

    return ret;
}

surface_t* new_surface(color_t color, vector_t *normal, int points_len, ...)
{
    surface_t *ret = calloc(1, sizeof(surface_t));

    va_list valist;

    ret->normal = normal;
    ret->points_len = points_len;
    ret->color = color;
 
    va_start(valist, points_len);

    ret->points = calloc(points_len, sizeof(surface_t*));

    for (int i = 0; i < points_len; i++) 
    {
        point_t *point = (point_t*)va_arg(valist, void*);
        ret->points[i] = point;
    }
 
    va_end(valist);

    return ret;
}

surface_t* copy_surface(surface_t *s)
{
    surface_t *ret = calloc(1, sizeof(surface_t));

    ret->color = s->color;
    if (ret->normal != NULL) {
    ret->normal = new_vector(s->normal->x, s->normal->y, s->normal->z);
    }

    for (int i = 0; i < s->points_len; i++)
    {
        add_point_to_surface(ret, new_point(
            s->points[i]->x,
            s->points[i]->y,
            s->points[i]->z
        ));
    }

    return ret;
}

point_t* new_point(double x, double y, double z) 
{
    point_t *ret = calloc(1, sizeof(point_t));
    ret->x = x;
    ret->y = y;
    ret->z = z;
    return ret;
}

vector_t* new_vector(double x, double y, double z)
{
    vector_t *ret = calloc(1, sizeof(vector_t));
    double mag = sqrt(powf(x, 2) + powf(y, 2) + powf(z, 2));
    ret->x = x / mag;
    ret->y = y / mag;
    ret->z = z / mag;
    return ret;
}

vector_t* vector_cross_product(vector_t *a, vector_t *b)
{
    vector_t *ret;
    ret = calloc(1, sizeof(vector_t));
    ret->x = a->y * b->z - a->z * b->y;
    ret->y = a->z * b->x - a->x * b->z;
    ret->z = a->x * b->y - a->y * b->x;
    return ret;
}

double vector_dot_product(vector_t *a, vector_t *b)
{
    return a->x * b->x + a->y + b->y + a->z + b->z;
}

double vector_magnitude(vector_t *a)
{
    return sqrt(pow(a->x, 2) + pow(a->y, 2) + pow(a->z, 2));
}

void add_surface_to_object(object_t *obj, surface_t *s)
{
    obj->surfaces_len = obj->surfaces_len + 1;
    if (obj->surfaces == NULL) {
        obj->surfaces = calloc(1, sizeof(surface_t));
    } else {
        obj->surfaces = realloc(obj->surfaces, obj->surfaces_len * sizeof(surface_t));
    }
    obj->surfaces[obj->surfaces_len - 1] = s;
}

void add_point_to_surface(surface_t *s, point_t *p)
{
    s->points_len = s->points_len + 1;
    if (s->points == NULL) {
        s->points = calloc(1, sizeof(point_t));
    } else {
        s->points = realloc(s->points, s->points_len * sizeof(point_t));
    }
    s->points[s->points_len - 1] = p;
}

void print_object(object_t* object)
{
    printf("object:\n");
    for (int i = 0; i < object->surfaces_len; i++)
    {
        print_surface(object->surfaces[i]);
    }
}

void print_surface(surface_t* surface)
{
    print_vector(surface->normal);
    for (int i = 0; i < surface->points_len; i++)
    {
        print_point(surface->points[i]);
    }
}

void print_point(point_t* point)
{
    printf("point : (%.3lf %.3lf %.3lf)\n", 
        point->x,
        point->y,
        point->z
    );
}

void print_vector(vector_t* normal)
{
    printf("normal : <%.3lf %.3lf %.3lf>\n", 
        normal->x,
        normal->y,
        normal->z
    );
}