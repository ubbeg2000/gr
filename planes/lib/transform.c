#include <stdio.h>
#include <math.h>

#include "transform.h"
#include "object.h"

void rotate_x(object_t *obj, double deg)
{
    surface_t *s;

    double rad = deg / 180 * M_PI;
    double cosrad = cos(rad);
    double sinrad = sin(rad);

    for (int i = 0; i < obj->surfaces_len; i++)
    {
        s = obj->surfaces[i];

        double y = s->normal->y, z = s->normal->z;
        
        s->normal->x = s->normal->x;
        s->normal->y = y * cosrad - z * sinrad;
        s->normal->z = y * sinrad + z * cosrad;

        for (int j = 0; j < s->points_len; j++)
        {
            y = s->points[j]->y;
            z = s->points[j]->z;

            s->points[j]->x = s->points[j]->x;
            s->points[j]->y = y * cosrad - z * sinrad;
            s->points[j]->z = y * sinrad + z * cosrad;
        }
    }
}

void rotate_y(object_t *obj, double deg)
{

}

void rotate_z(object_t *obj, double deg)
{

}