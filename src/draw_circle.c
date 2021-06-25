/*
This file was used to draw Circles around Text, however,
I moved to using bitmaps so it is no longer used,
however I keep it since I wrote mid-point algorithm in it
*/
#include "draw_circle.h"
#include "sdl_surfaces_header.h"

extern SDL_Surface* gWindowSurface;
extern Uint32 glyphColor;
void DrawPixel(int x, int y)
{
    SDL_Rect onePixelRect = { x, y, 1, 1 };
    SDL_FillRect(gWindowSurface, &onePixelRect, glyphColor);
}

//I modified the algorithm a bit but the concept is the same
//https://www.bu.edu.eg/portal/uploads/Computers%20and%20Informatics/Computer%20Science/4899/crs-12417/Files/Midpoint%20Circle%20Algorithm.pdf
void DrawCircle(int Cx, int Cy, int Radius)
{
    int X = -Radius;
    int Y = 0;

    int EP = 0;
    int EP0;
    int EP1;

    while (-X >= Y)
    {
        DrawPixel(Cy + X, Cx + Y);
        DrawPixel(Cy + X, Cx - Y);
        DrawPixel(Cy - X, Cx + Y);
        DrawPixel(Cy - X, Cx - Y);

        DrawPixel(Cy + Y, Cx + X);
        DrawPixel(Cy + Y, Cx - X);
        DrawPixel(Cy - Y, Cx + X);
        DrawPixel(Cy - Y, Cx - X);

        EP += 1;
        EP0 = EP + 2 * X;
        EP1 = EP + 2 * Y;

        if (-EP0 <= EP1)
        {
            EP = EP0;
            ++X;
        }
        else
        {
            EP = EP1;
            ++Y;
        }
    }
}

void DrawDisk(int x, int y, int radius)
{
    for (int currentCircle = 0; currentCircle < radius; ++currentCircle)
    {
        DrawCircle(x, y, radius - currentCircle);
    }
}
