#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define CANVAS_HEIGHT 70
#define CANVAS_WIDTH 200

#include "lib/color.h"
#include "lib/object.h"
#include "lib/raster.h"
#include "lib/transform.h"

object_t *new_torus(double r_in, double r_out, double z)
{
    object_t *ret = calloc(1, sizeof(object_t));

    double radius = (r_out - r_in) / 2;
    point_t center = {.x = 0, .y = r_in + radius, .z = z};

    int degree_increment = 20;
    surface_t* initial_surfaces[360 / degree_increment];

    for (int i = 0; i < 360 / degree_increment; i++)
    {
        double rad = i * degree_increment * M_PI / 180;
        initial_surfaces[i] = new_surface(
            WHITE, new_vector(0, sin(rad), cos(rad)), 1, 
            new_point(0, center.y + radius * sin(rad), radius * cos(rad))
        );
    }

    for (int i = 0; i < 360 / degree_increment; i++)
    {
        for (int j = 0; j < 360 / degree_increment; j++)
        {
            surface_t *ns = copy_surface(initial_surfaces[j]);
            rotate_surface_z(ns, i * degree_increment);
            add_surface_to_object(ret, ns);
        }
    }

    return ret;
}


int main()
{
    double canvas_depth = -30;

    object_t *tri = new_object(1,
        new_surface(WHITE, new_vector(1, 1, 1), 3,
            new_point(0, -100, 70),
            new_point(0, 100, 70),
            new_point(100, -100, 70)
        ),
        new_surface(0x000010FF, new_vector(6, 6, 6), 3,
            new_point(0, 0, 9),
            new_point(0, 8, 9),
            new_point(8, 0, 9)
        )
    );

    object_t *torus = new_torus(3, 7, 25);
    canvas_t *canvas = new_canvas(CANVAS_WIDTH, CANVAS_HEIGHT, canvas_depth);
    useconds_t animation_delay = 40000;

    int angle = 10;
    while (1)
    {
        // for (int i = 0; i < 10; i++) 
        // {
        //     translate(torus, 0, -0.5, 0);

        //     clear_canvas(canvas);
        //     rasterize_points(canvas, torus, -20);

        //     system("clear"); 
        //     print_canvas(canvas, ASCII_DARK_BG);

        //     usleep(animation_delay);
        // }

        // for (int i = 0; i <= 0; i++) 
        // {
        //     translate(torus, -0.5, -0.5, 0);

        //     clear_canvas(canvas);
        //     rasterize_points(canvas, torus, -20);

        //     system("clear"); 
        //     print_canvas(canvas, ASCII_DARK_BG);

        //     usleep(animation_delay);
        // }

        // for (int i = 0; i < 10; i++) 
        // {
        //     set_canvas_depth(canvas, canvas_depth-i*0.5);

        //     clear_canvas(canvas);
        //     rasterize_points(canvas, torus, -20);

        //     system("clear"); 
        //     print_canvas(canvas, ASCII_DARK_BG);

        //     usleep(animation_delay);
        // }

        // for (int i = 10; i >= 0; i--) 
        // {
        //     set_canvas_depth(canvas, canvas_depth-i*0.5);

        //     clear_canvas(canvas);
        //     rasterize_points(canvas, torus, -20);

        //     system("clear"); 
        //     print_canvas(canvas, ASCII_DARK_BG);

        //     usleep(animation_delay);
        // }

        for (int i = 0; i < 18 + 36; i++) 
        {
            rotate(torus, angle, angle, angle);

            clear_canvas(canvas);
            rasterize_points(canvas, torus, -20);

            system("clear"); 
            print_canvas(canvas, ASCII_DARK_BG);

            usleep(animation_delay);
        }

        // for (int i = 0; i < 18 + 36; i++) 
        // {
        //     rotate_y(torus, angle);

        //     clear_canvas(canvas);
        //     rasterize_points(canvas, torus, -20);

        //     system("clear"); 
        //     print_canvas(canvas, ASCII_DARK_BG);

        //     usleep(animation_delay);
        // }

        // for (int i = 0; i < 18 + 36; i++) 
        // {
        //     rotate_y(torus, angle);

        //     clear_canvas(canvas);
        //     rasterize_points(canvas, torus, -20);

        //     system("clear"); 
        //     print_canvas(canvas, ASCII_DARK_BG);

        //     usleep(animation_delay);
        // }
    }
    
    return 0;
}