#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>

// in the cartesian coordinate system used, the z axis is going
// 'out' of the screen

// definitions for the screen, scale, and camera distance
#define WIDTH 80
#define HEIGHT 40
#define DIST 3.0
#define SCALE 30.0

char screen[HEIGHT][WIDTH];
float angle;

typedef struct
{
    float x, y, z;
} Vec;

int main()
{
    Vec cube[8] =
    {
        {0, 0, 0},      // upper right vertex
        {0, 0, 1},     // lower right vertex
        {1, 0, 0},     // upper left vertex
        {1, 0, 1},    // lower left vertex
        {0, 1, 0},     // upper right vertex (back)
        {0, 1, 1},    // lower right vertex (back)
        {1, 1, 0},    // upper left vertex (back)
        {1, 1, 1}    // lower left vertex (back)
    };

    while (1)
    {
        // clears the terminal
        system("cls");

        // clears the screen
        for (int i = 0; i < HEIGHT; i++)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                screen[i][j] = ' ';
            }
        }

        // projects the points on the screen
        // here we're gonna have to project a 3d coordinate in a 2d plane
        for (int i = 0; i < 8; i++)
        {
            float x0 = cube[i].x;
            float y0 = cube[i].y;
            float z0 = cube[i].z;

            // rotates the cube along the y axis

            float x = x0*cos(angle) + sin(angle) * z0;
            float y = y0;
            float z = -sin(angle) * x0 + cos(angle) * z0;

            z += DIST;

            int sx = (int)(x / z * SCALE + WIDTH/2);
            int sy = (int)(-y / z * SCALE + HEIGHT/2);

            if (sx >= 0 && sx < WIDTH && sy >= 0 && sy < HEIGHT)
                screen[sy][sx] = '*';
        }

        // prints the screen
        for (int i = 0; i < HEIGHT; i++)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                putchar(screen[i][j]);
            }
            putchar('\n');
        }

        angle += 0.05;

        Sleep(500);
    }
    return 0;
}
