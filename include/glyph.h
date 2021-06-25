#ifndef GLYPH_H
#define GLYPH_H
#include "SDL.h"

#define GLYPH_WIDTH 44
#define GLYPH_HEIGHT 70
#define GLYPHS_PER_ROW 10

enum
{
    GLYPH_ZERO  = 0,
    GLYPH_ONE   = 1,
    GLYPH_TWO   = 2,
    GLYPH_THREE = 3,
    GLYPH_FOUR  = 4,
    GLYPH_FIVE  = 5,
    GLYPH_SIX   = 6,
    GLYPH_SEVEN = 7,
    GLYPH_EIGHT = 8,
    GLYPH_NINE  = 9,
    GLYPH_COLON = 10,
    GLYPH_COUNT = 11
};

static const Uint8 glyphIndices[GLYPH_COUNT] = {
    GLYPH_ZERO,
    GLYPH_ONE,
    GLYPH_TWO,
    GLYPH_THREE,
    GLYPH_FOUR,
    GLYPH_FIVE,
    GLYPH_SIX,
    GLYPH_SEVEN,
    GLYPH_EIGHT,
    GLYPH_NINE,
    GLYPH_COLON,
};

void PutGlyphOnSurface(SDL_Surface* destSurface, Uint8 glyphIndex, SDL_Rect destRect);
#endif
