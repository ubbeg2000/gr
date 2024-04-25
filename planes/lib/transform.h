#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "object.h"

void rotate_x(object_t *obj, double deg);

void rotate_y(object_t *obj, double deg);

void rotate_z(object_t *obj, double deg);

void rotate(object_t *obj, double deg_x, double deg_y, double deg_z);

void translate(object_t *obj, double x, double y, double z);

void rotate_surface_x(surface_t *s, double deg);

void rotate_surface_y(surface_t *s, double deg);

void rotate_surface_z(surface_t *s, double deg);

#endif