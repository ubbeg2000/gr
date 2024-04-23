#ifndef OBJECT_H_
#define OBJECT_H_

#include <stdint.h>

#include "color.h"


typedef struct point_t 
{
    double x, y, z;
} point_t;

typedef point_t vector_t;

typedef struct surface_t 
{
    point_t **points;
    point_t *normal;
    color_t color;
    int points_len;
} surface_t;

typedef struct object_t 
{
    surface_t **surfaces;
    int surfaces_len;
} object_t;

object_t* new_object(int surfaces_len, ...);

surface_t* new_surface(color_t color, vector_t *normal, int points_len, ...);

point_t* new_point(double x, double y, double z);

vector_t* new_vector(double x, double y, double z);

vector_t* vector_cross_product(vector_t *a, vector_t *b);

void print_object(object_t *object);

void print_surface(surface_t *surface);

void print_point(point_t *point);

void print_vector(vector_t *normal);

#endif