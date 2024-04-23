#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define CANVAS_HEIGHT 100
#define CANVAS_WIDTH 100

#include "lib/color.h"
#include "lib/object.h"
#include "lib/raster.h"
#include "lib/transform.h"


int main()
{
    object_t *cube = new_object(2,
        new_surface(WHITE, new_vector(1, 1, 1), 3,
            new_point(0, -20, 10),
            new_point(0, 20, 10),
            new_point(20, -20, 10)
        ),
        new_surface(0x000010FF, new_vector(6, 6, 6), 3,
            new_point(0, 0, 9),
            new_point(0, 8, 9),
            new_point(8, 0, 9)
        )
    );
    // print_object(cube);
    canvas_t *canvas = new_canvas(CANVAS_WIDTH, CANVAS_HEIGHT, -45);

    int angle = 10;
    int angle_accum = 0;
    while (1)
    {
        rotate_x(cube, angle);

        clear_canvas(canvas);
        rasterize_surfaces(canvas, cube, -18);

        system("clear"); 
        print_canvas(canvas, ASCII_DARK_BG);

        angle_accum += 1;
        printf("%d\n", angle_accum % 360);

        usleep(50000);
    }
    
    return 0;
}