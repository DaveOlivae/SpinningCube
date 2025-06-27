#include <stdio.h>

// in the cartesian coordinate system used, the z axis is going
// 'out' of the screen

// definitions for the screen, scale, and camera distance
#define WIDTH 80
#define HEIGHT 40
#define DIST 3.0
#define SCALE 20.0

char screen[HEIGHT][WIDTH];

typedef struct
{
    float x, y, z;
} Vec;

int main()
{
    Vec cube[8] =
    {
        {1, 1, 1},      // upper right vertex
        {1, 1, -1},     // lower right vertex
        {1, -1, 1},     // upper left vertex
        {1, -1, -1},    // lower left vertex
        {-1, 1, 1},     // upper right vertex (back)
        {-1, 1, -1},    // lower right vertex (back)
        {-1, -1, 1},    // upper left vertex (back)
        {-1, -1, -1}    // lower left vertex (back)
    };

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
        float x = cube[i].x;
        float y = cube[i].y;
        float z = cube[i].z + DIST; // we to add a distance, so that the cube is not to close to the camera

        x = cube[i].x = x * cos(0.5) + z * sin(0.5);
        z = cube[i].z = -x * sin(0.5) + z * cos(0.5);

        int sx = (int)(x / z * SCALE + WIDTH/2);
        int sy = (int)(y / z * SCALE + HEIGHT/2);

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

    return 0;
}
