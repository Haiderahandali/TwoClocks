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
    int X = Radius;
    int Y = 0;

    int EP = 0;
    int EP0;
    int EP1;

    while (X > Y)
    {
        DrawPixel(Cy + X, Cx + Y);
        DrawPixel(Cy + X, Cx - Y);
        DrawPixel(Cy - X, Cx + Y);
        DrawPixel(Cy - X, Cx - Y);

        DrawPixel(Cy + Y, Cx + X);
        DrawPixel(Cy + Y, Cx - X);
        DrawPixel(Cy - Y, Cx + X);
        DrawPixel(Cy - Y, Cx - X);

        /* calculating the error for the next point and select the one with less error.
         from the circle equation, the difference between the 2 errors is either 2X or 2Y
         EP stands for the previous error, Ep1 is the error if we moved in the Y direction, Ep2 if we moved in the X direction
        */
        EP += 1;
        EP0 = -EP + (X>>1);
        EP1 = EP  + (Y>>1);

        if (EP0 < EP1)
        {
            EP = -EP0;
            --X;
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
