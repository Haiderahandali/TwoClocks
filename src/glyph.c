#include "glyph.h"

void PutGlyphOnSurface(SDL_Surface* destSurface, Uint8 glyphIndex, SDL_Rect destRect)
{

    SDL_Rect glyphRect = {
        glyphIndex * GLYPH_WIDTH,
        1 + GLYPH_HEIGHT * (glyphIndex / GLYPHS_PER_ROW),
        GLYPH_WIDTH, GLYPH_HEIGHT
    };

    SDL_BlitSurface(
        gFontSurface,
        &glyphRect,
        destSurface,
        &destRect
    );
}
