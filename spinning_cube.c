#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <windows.h>
    void screen_sleep(int miliseconds)
    {
        Sleep(miliseconds);
    }
#else
    #include <unistd.h>
    void screen_sleep(int miliseconds)
    {
        usleep(miliseconds * 1000);
    }
#endif

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

void clear_screen()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            screen[i][j] = ' ';
        }
    }
}

void print_screen()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            putchar(screen[i][j]);
        }
        putchar('\n');
    }
}

int main()
{
    int number_of_points = 12;

    // so, right now the cube is merely a list of points, each with z y z coordinates
    Vec cube[] =
    {
        {0, 0, 0},      // upper right vertex
        {0, 0, 1},     // lower right vertex
        {1, 0, 0},     // upper left vertex
        {1, 0, 1},    // lower left vertex
        {0, 1, 0},     // upper right vertex (back)
        {0.06, 1, 0},
        {0.12, 1, 0},
        {0.18, 1, 0},
        {0, 1, 1},    // lower right vertex (back)
        {1, 1, 0},    // upper left vertex (back)
        {1, 1, 1},   // lower left vertex (back)
        
    };

    while (1)
    {
        // clears the terminal
        system("clear");

        // clears the screen
        clear_screen();    

        // projects the points on the screen
        // here we're gonna have to project a 3d coordinate in a 2d plane
        for (int i = 0; i < number_of_points; i++)
        {
            // original x, y and z values
            float x0 = cube[i].x;
            float y0 = cube[i].y;
            float z0 = cube[i].z;

            // rotates the cube along the y axis
                // new x, y and z values
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
        print_screen();    

        angle += 0.05;

        screen_sleep(500);
    }
    return 0;
}
