#ifndef PRINT_TIME_H
#define PRINT_TIME_H

#include "glyph.h"

#define SPACE_BETWEEN_MINTS_AND_SECONDS 20
#define PADDING_BETWEEN_NUMBERS 5
#define COLON_WIDTH 20
#define COLON_HEIGHT 70
extern SDL_Surface* gClockBgSurface;

void DrawClock(SDL_Surface* destSurface, SDL_Rect startRect, int minutes, int seconds);

#endif
