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

        double y, z;

        if (s->normal != NULL) {
            y = s->normal->y;
            z = s->normal->z;
            
            s->normal->x = s->normal->x;
            s->normal->y = y * cosrad - z * sinrad;
            s->normal->z = y * sinrad + z * cosrad;
        }

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
    surface_t *s;

    double rad = deg / 180 * M_PI;
    double cosrad = cos(rad);
    double sinrad = sin(rad);

    for (int i = 0; i < obj->surfaces_len; i++)
    {
        s = obj->surfaces[i];

        double x, z;
        if (s->normal != NULL) {
            x = s->normal->y;
            z = s->normal->z;
            
            s->normal->x = x * cosrad + z * sinrad;
            s->normal->y = s->normal->y;
            s->normal->z = -x * sinrad + z * cosrad;
        }

        for (int j = 0; j < s->points_len; j++)
        {
            x = s->points[j]->x;
            z = s->points[j]->z;

            s->points[j]->x = x * cosrad + z * sinrad;
            s->points[j]->y = s->points[j]->y;
            s->points[j]->z = -x * sinrad + z * cosrad;
        }
    }

}

void rotate_z(object_t *obj, double deg)
{
    surface_t *s;

    double rad = deg / 180 * M_PI;
    double cosrad = cos(rad);
    double sinrad = sin(rad);

    for (int i = 0; i < obj->surfaces_len; i++)
    {
        s = obj->surfaces[i];

        double x, y;

        if (s->normal != NULL) {
            x = s->normal->x;
            y = s->normal->y;
            
            s->normal->x = x * cosrad - y * sinrad;
            s->normal->y = x * sinrad + y * cosrad;
            s->normal->z = s->normal->z;
        }

        for (int j = 0; j < s->points_len; j++)
        {
            x = s->points[j]->x;
            y = s->points[j]->y;
        
            s->points[j]->x = x * cosrad - y * sinrad;
            s->points[j]->y = x * sinrad + y * cosrad;
            s->points[j]->z = s->points[j]->z;
        }
    }
}

void rotate(object_t *obj, double deg_x, double deg_y, double deg_z)
{
    rotate_x(obj, deg_x);
    rotate_y(obj, deg_y);
    rotate_z(obj, deg_z);
}

void translate(object_t *obj, double x, double y, double z)
{
    surface_t *s;
    for (int i = 0; i < obj->surfaces_len; i++)
    {
        s = obj->surfaces[i];
        for (int j = 0; j < s->points_len; j++)
        {
            s->points[j]->x += x;
            s->points[j]->y += y;
            s->points[j]->z += z;
        }
    }
}

void rotate_surface_x(surface_t *s, double deg)
{
    double rad = deg / 180 * M_PI;
    double cosrad = cos(rad);
    double sinrad = sin(rad);

    double y, z;
    if (s->normal != NULL) {
        y = s->normal->y; 
        z = s->normal->z;
        
        s->normal->x = s->normal->x;
        s->normal->y = y * cosrad - z * sinrad;
        s->normal->z = y * sinrad + z * cosrad;
    }

    for (int j = 0; j < s->points_len; j++)
    {
        y = s->points[j]->y;
        z = s->points[j]->z;

        s->points[j]->x = s->points[j]->x;
        s->points[j]->y = y * cosrad - z * sinrad;
        s->points[j]->z = y * sinrad + z * cosrad;
    }
}

void rotate_surface_y(surface_t *s, double deg)
{
    double rad = deg / 180 * M_PI;
    double cosrad = cos(rad);
    double sinrad = sin(rad);

    double x, z;

    if (s->normal != NULL) {
        x = s->normal->x; 
        z = s->normal->z;
        
        s->normal->x = x * cosrad + z * sinrad;
        s->normal->y = s->normal->y;
        s->normal->z = -x * sinrad + z * cosrad;
    }

    for (int j = 0; j < s->points_len; j++)
    {
        x = s->points[j]->x;
        z = s->points[j]->z;

        s->points[j]->x = x * cosrad + z * sinrad;
        s->points[j]->y = s->points[j]->y;
        s->points[j]->z = -x * sinrad + z * cosrad;
    }
}

void rotate_surface_z(surface_t *s, double deg)
{

    double rad = deg / 180 * M_PI;
    double cosrad = cos(rad);
    double sinrad = sin(rad);

    double x, y;

    if (s->normal != NULL) {
        x = s->normal->x;
        y = s->normal->y;

        s->normal->x = x * cosrad - y * sinrad;
        s->normal->y = x * sinrad + y * cosrad;
        s->normal->z = s->normal->z;
    }
    

    for (int j = 0; j < s->points_len; j++)
    {
        x = s->points[j]->x;
        y = s->points[j]->y;
    
        s->points[j]->x = x * cosrad - y * sinrad;
        s->points[j]->y = x * sinrad + y * cosrad;
        s->points[j]->z = s->points[j]->z;
    }
}