#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

#define PI 3.141592654

#define CSIZE 101

char initial[CSIZE][CSIZE];

int min_int(int a, int b) 
{
    return a < b ? a : b;
}

int max_int(int a, int b) 
{
    return a > b ? a : b;
}

float triangle_area(int x1, int y1, int x2, int y2, int x3, int y3)
{
   return fabs((x1*(y2-y3) + x2*(y3-y1)+ x3*(y1-y2))/2.0);
}
  
int is_inside_triangle(int x1, int y1, int x2, int y2, int x3, int y3, int px, int py)
{   
   float a = triangle_area(x1, y1, x2, y2, x3, y3);
  
   float a1 = triangle_area(px, py, x2, y2, x3, y3);
  
   float a2 = triangle_area(x1, y1, px, py, x3, y3);
   
   float a3 = triangle_area(x1, y1, x2, y2, px, py);
    
   return a == a1 + a2 + a3 ? 1 : 0;
}

void draw_triangle(char canvas[CSIZE][CSIZE], int x1, int y1, int x2, int y2, int x3, int y3, char fill) 
{
    int min_x = min_int(x1, min_int(x2, x3));
    int min_y = min_int(y1, min_int(y2, y3));
    int max_x = max_int(x1, max_int(x2, x3));
    int max_y = max_int(y1, max_int(y2, y3));

    for (int i = min_y; i <= max_y; i++) {
        for (int j = min_x; j <= max_x; j++) {
            if (is_inside_triangle(x1, y1, x2, y2, x3, y3, j, i) == 1) {
                canvas[i][j] = fill;
            }
        }
    }
}

void draw_circle(char canvas[CSIZE][CSIZE], int x, int y, int r, char fill)
{
    int min_x = x - r;
    int min_y = y - r;
    int max_x = x + r;
    int max_y = y + r;

    for (int i = min_y; i <= max_y; i++) {
        for (int j = min_x; j <= max_x; j++) {
            int rx = abs(j - x);
            int ry = abs(i - y);

            float rr = sqrt(powf(rx, 2) + powf(ry, 2));

            if (rr <= r) {
                canvas[i][j] = fill;
            }
        }
    }
}

int rotate_x(int x, int y, double deg)
{
    double rad = deg * PI / 180;
    return (int)floorf(x * cos(rad) - y * sin(rad));
}

int rotate_y(int x, int y, double deg)
{
    double rad = deg * PI / 180;
    return (int)floorf(x * sin(rad) + y * cos(rad));
}

void print_canvas(char canvas[CSIZE][CSIZE]) {
    char buffer[CSIZE * CSIZE + CSIZE + 1];
    for (int i = 0; i < CSIZE * CSIZE; i++) {
        buffer[i] = '\n';
    }
    for (int i = 0; i < CSIZE; i++) {
        for (int j = 0; j < CSIZE; j++) {
            buffer[i*CSIZE+j+i] = canvas[i][j];
        }
    }
    buffer[CSIZE * CSIZE + CSIZE] = '\0';
}

int main()
{
    char blank[CSIZE][CSIZE];

    memset(initial, ' ', CSIZE*CSIZE*sizeof(char));

    draw_circle(initial, 40, 40, 18, '.');

    draw_circle(initial, 40, 40, 9, ' ');

    draw_triangle(initial, 32, 45, 32, 57, 57, 57, '#');

    print_canvas(initial);

    // return 0;

    int angle = 0;
    while (1) {
        memset(blank, ' ', CSIZE*CSIZE*sizeof(char));
        angle = (angle + 1) % 360;

        for (int i = 0; i < CSIZE; i++) {
            for (int j = 0; j < CSIZE; j++) {
                int x = j - CSIZE / 2;
                int y = i - CSIZE / 2;

                int x_rot = rotate_x(x, y, (double)angle);
                int y_rot = rotate_y(x, y, (double)angle);

                int i_rot = (y_rot + CSIZE / 2);
                int j_rot = (x_rot + CSIZE / 2);

                // printf("%d %d\n", i_rot, j_rot);

                if (i_rot >= 0 && j_rot >= 0) {
                    blank[i_rot][j_rot] = initial[i][j];
                }

            }
        }

        system("clear"); 
        print_canvas(blank);
        // printf("%d\n", angle);
        usleep(25000);
        // d = d+1;
    }
    // printf("UHUY\n");


    return 0;
}