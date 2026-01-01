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

Vec rotate_y(float x0, float y0, float z0)
{
    // rotates the cube along the y axis
    // new x, y and z values
    float x = x0*cos(angle) + sin(angle) * z0; 
    float y = y0; 
    float z = -sin(angle) * x0 + cos(angle) * z0;

    Vec rotated_vec = {x, y, z};
    
    return rotated_vec;
}

int main()
{
    int number_of_points = 8;

    // so, right now the cube is merely a list of points, each with z y z coordinates
    Vec cube[] =
    {
        {0, 0, 0},      // p1: upper right vertex
        {0, 0, 1},      // p2: lower right vertex
        {1, 0, 0},      // p3: upper left vertex
        {1, 0, 1},      // p4: lower left vertex
        {0, 1, 0},      // p5: upper right vertex (back)
        {0, 1, 1},      // p6: lower right vertex (back)
        {1, 1, 0},      // p7: upper left vertex (back)
        {1, 1, 1},      // p8: lower left vertex (back)
        
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
            Vec rotated_vec = rotate_y(cube[i].x, cube[i].y, cube[i].z);

            rotated_vec.z += DIST;

            int sx = (int)(rotated_vec.x / rotated_vec.z * SCALE + WIDTH/2.0);
            int sy = (int)(-rotated_vec.y / rotated_vec.z * SCALE + HEIGHT/2.0);

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
