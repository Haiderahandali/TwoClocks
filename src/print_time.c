#include "print_time.h"

//tweaked values for centering the font
//inside the clock
#define XPADDING 25
#define YPADDING 15

static SDL_Rect clockBgRectSrc = { 0, 0, 256, 100 };

void DrawClock(SDL_Surface* destSurface, SDL_Rect startRect, int minutes, int seconds)
{

    //----- Draw the Clock Background ----//
    SDL_Rect clockBgRecTDest = { startRect.x - XPADDING, startRect.y - YPADDING,
        clockBgRectSrc.w, clockBgRectSrc.h };

    SDL_BlitSurface(gClockBgSurface, &clockBgRectSrc, destSurface, &clockBgRecTDest);

    //---------Drawing Minutes----------//
    PutGlyphOnSurface(destSurface, glyphIndices[minutes / 10], startRect);

    startRect.x += PADDING_BETWEEN_NUMBERS + startRect.w;
    PutGlyphOnSurface(destSurface, glyphIndices[minutes % 10], startRect);

    //---------Drawing the colon `:`  for the time (20:30)
    { // For some reasons, passing GLYPH_COLON doesn't display it, so I hard coded it for now
        SDL_Rect colonRectDest = { startRect.x + startRect.w, startRect.y, COLON_WIDTH, COLON_HEIGHT };
        SDL_Rect colonRectSrc  = { 455, 1, COLON_WIDTH, COLON_HEIGHT };
        SDL_BlitSurface(gFontSurface, &colonRectSrc, destSurface, &colonRectDest);
    }

    //---------Drawing Seconds----------//
    startRect.x += SPACE_BETWEEN_MINTS_AND_SECONDS + startRect.w;
    PutGlyphOnSurface(destSurface, glyphIndices[seconds / 10], startRect);

    startRect.x += PADDING_BETWEEN_NUMBERS + startRect.w;
    PutGlyphOnSurface(destSurface, glyphIndices[seconds % 10], startRect);
}
