#include "core.h"
#include "load_bmp.h"
#include "glyph.h"
#include "print_time.h"
#include "construct_absolute_paths.h"

//Gets initalised in init()
SDL_Surface* gWindowSurface;
SDL_Window* gWindow;
SDL_Surface* gFontSurface;
SDL_Surface* gBackgroundSurface;
SDL_Surface* gClockBgSurface;

Uint32 bgColor;
Uint32 glyphColor;
Uint32 start;
Uint32 previousTime;

int gClockTwoTimer;
int gClockOneTimer;

static bool useClockOne = true;

Uint32 delay   = 20; //50 FPS
Uint32 counter = 0;

char FONT_PATH[100];
char BG_PATH[100];
char CLOCK_BG_PATH[100];
char AUDIO_PATH[100] = "/Users/alia/dev/TwoClocks/./assets/alarmMusic.mp3";

bool IS_RUNNING
    = true;

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != SDL_SUCCESS)
    {
        SDL_Log("could not init SDL_VIDEO Error is %s\n", SDL_GetError());
        return false;
    }

    gWindow = SDL_CreateWindow("Two Clocks", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (gWindow == FAILED_TO_INIT_WINDOW)

    {
        SDL_Log("could not create Window Error is %s\n", SDL_GetError());
        return false;
    }

    gWindowSurface = SDL_GetWindowSurface(gWindow);
    if (gWindowSurface == FAILED_TO_GET_WINDOW_SURFACE)
    {
        SDL_Log("could not get window surface, Error is %s\n", SDL_GetError());
        return false;
    }

    bgColor = SDL_MapRGBA(gWindowSurface->format, 184, 219, 239, 0XFF); //white Bg

    start        = SDL_GetTicks(); //initalise the time of our app
    previousTime = start;
    glyphColor   = SDL_MapRGBA(gWindowSurface->format, 0X00, 0X00, 0X00, 0XFF); // text color is black

    gClockOneTimer = FIRST_CLOCK_TIME;
    gClockTwoTimer = SECND_CLOCK_TIME;

    ConstuctPaths(AUDIO_PATH,
        CLOCK_BG_PATH,
        BG_PATH,
        FONT_PATH);

    LoadBMPS();
    return true;
}

void EventLoop()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            IS_RUNNING = false;
        }
    }
}

void Render()
{
    //clear the background to the white color

    // SDL_FillRect(gWindowSurface, NULL, bgColor);
    SDL_BlitSurface(gBackgroundSurface, NULL, gWindowSurface, NULL);

    SDL_Rect ClockOneRect = { 70, 245, GLYPH_WIDTH, GLYPH_HEIGHT };
    SDL_Rect ClockTwoRect = { 370, 245, GLYPH_WIDTH, GLYPH_HEIGHT };

    DrawClock(gWindowSurface, ClockOneRect, gClockOneTimer / 60, gClockOneTimer % 60);
    DrawClock(gWindowSurface, ClockTwoRect, gClockTwoTimer / 60, gClockTwoTimer % 60);
}

void CloseApp()
{
    SDL_DestroyWindow(gWindow);
    gWindow        = NULL;
    gWindowSurface = NULL;
}

void WaitLoop()
{
    ++counter;
    Uint32 target      = counter * delay;
    Uint32 timeElapsed = SDL_GetTicks() - start;
    if (target > timeElapsed)
    {
        SDL_Delay(target - timeElapsed);
    }
}

void Update()
{

    SDL_UpdateWindowSurface(gWindow);
    UpdateTimeInSeconds();
}
void UpdateTimeInSeconds(void)
{
    static Uint32 timeElapsed = 0;
    Uint32 currentTime        = SDL_GetTicks();
    Uint32 const duration     = 1000; /* in milli seconds */
    timeElapsed += currentTime - previousTime;
    while (timeElapsed > duration)
    {
        timeElapsed -= duration;

        if (useClockOne)
        {

            if (--gClockOneTimer < 1)
            {
                useClockOne    = false;
                gClockOneTimer = FIRST_CLOCK_TIME;
                PlayAlarm();
            }
        }
        else
        {
            if (--gClockTwoTimer < 1)
            {
                useClockOne    = true;
                gClockTwoTimer = SECND_CLOCK_TIME;
                PlayAlarm();
            }
        }
    }
    previousTime = currentTime;
}

void LoadBMPS()
{
    bmp_file_t bmpFont;
    bmp_file_t bmpBg;
    bmp_file_t bmpClockBG;

    ReadBMP(&bmpFont, FONT_PATH);
    ReadBMP(&bmpBg, BG_PATH);
    ReadBMP(&bmpClockBG, CLOCK_BG_PATH);

    gFontSurface = SDL_CreateRGBSurfaceFrom(bmpFont.pixelDataPointer,
        (int)bmpFont.width, (int)bmpFont.height, (int)bmpFont.bpp,
        (int)(bmpFont.bpp * bmpFont.width / 8),
        Rmask, Gmask, Bmask, Amask);

    gBackgroundSurface = SDL_CreateRGBSurfaceFrom(bmpBg.pixelDataPointer,
        (int)bmpBg.width, (int)bmpBg.height, (int)bmpBg.bpp,
        (int)(bmpBg.bpp * bmpBg.width / 8),
        Rmask, Gmask, Bmask, Amask);

    gClockBgSurface = SDL_CreateRGBSurfaceFrom(bmpClockBG.pixelDataPointer,
        (int)bmpClockBG.width, (int)bmpClockBG.height, (int)bmpClockBG.bpp,
        (int)(bmpClockBG.bpp * bmpClockBG.width / 8),
        Rmask, Gmask, Bmask, Amask);
}
