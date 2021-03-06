#include "core.h"
#include "load_bmp.h"
#include "glyph.h"
#include "print_time.h"
#include "construct_absolute_paths.h"
#include "audio.h"

#define PATH_BUFFER_SIZE 100

//Gets initalised in init()
static SDL_Window* gWindow;

SDL_Surface* gWindowSurface;
SDL_Surface* gFontSurface;
SDL_Surface* gClockBgSurface;

static SDL_Surface* gBackgroundSurface = NULL;

int gFirstClockTime;
int gSecondClockTime;

static Uint32 start;
static Uint32 previousTime;

static int gClockTwoTimer;
static int gClockOneTimer;

static bool useClockOne = true;

static Uint32 delay   = 20; //50 FPS
static Uint32 counter = 0;

static char gBackgroundPath[PATH_BUFFER_SIZE];
static char gFontPath[PATH_BUFFER_SIZE];
static char gClockBackgroundPath[PATH_BUFFER_SIZE];
static char gAudioPath[PATH_BUFFER_SIZE];

static void* gBmpArray[3];

bool IS_RUNNING = true;

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

    //Timer initialising
    start        = SDL_GetTicks(); //initalise the time of our app
    previousTime = start;

    gClockOneTimer = gFirstClockTime;
    gClockTwoTimer = gSecondClockTime;

    // constructing Absolute paths for assets (audio and images)
    ConstuctPaths(gAudioPath,
        gClockBackgroundPath,
        gBackgroundPath,
        gFontPath);

    // initialise sound components
    InitAudio(gAudioPath);

    //load images in bmp format
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

    SDL_BlitSurface(gBackgroundSurface, NULL, gWindowSurface, NULL);

    SDL_Rect ClockOneRect = { 70, 245, GLYPH_WIDTH, GLYPH_HEIGHT };
    SDL_Rect ClockTwoRect = { 370, 245, GLYPH_WIDTH, GLYPH_HEIGHT };

    DrawClock(gWindowSurface, ClockOneRect, gClockOneTimer / 60, gClockOneTimer % 60);
    DrawClock(gWindowSurface, ClockTwoRect, gClockTwoTimer / 60, gClockTwoTimer % 60);
}

void CloseApp()
{

    //freeing SDL components
    SDL_DestroyWindow(gWindow);
    SDL_FreeSurface(gFontSurface);
    SDL_FreeSurface(gClockBgSurface);
    SDL_FreeSurface(gBackgroundSurface);

    //freeing bitmap files
    for (int i = 0; i < 3; ++i)
    {
        free(gBmpArray[i]);
    }

    gWindow            = NULL;
    gWindowSurface     = NULL;
    gClockBgSurface    = NULL;
    gBackgroundSurface = NULL;
    gFontSurface       = NULL;
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
                gClockOneTimer = gFirstClockTime;
                PlayAlarm();
            }
        }
        else
        {
            if (--gClockTwoTimer < 1)
            {
                useClockOne    = true;
                gClockTwoTimer = gSecondClockTime;
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

    ReadBMP(&bmpFont, gFontPath);
    ReadBMP(&bmpBg, gBackgroundPath);
    ReadBMP(&bmpClockBG, gClockBackgroundPath);

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

    gBmpArray[0] = bmpBg.pixelDataPointer;
    gBmpArray[1] = bmpFont.pixelDataPointer;
    gBmpArray[2] = bmpClockBG.pixelDataPointer;
}
