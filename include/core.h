#ifndef CORE_H
#define CORE_H
#include "SDL.h"

#define SDL_SUCCESS 0
#define FAILED_TO_INIT_WINDOW NULL
#define FAILED_TO_GET_WINDOW_SURFACE NULL
#define WHITE 0XFFFFFFFF

int FIRST_CLOCK_TIME;
int SECND_CLOCK_TIME;
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

typedef enum
{
    false,
    true
} bool;

extern char FONT_PATH[];
extern char BG_PATH[];

extern SDL_Window* gWindow;

extern SDL_Surface* gWindowSurface;
extern SDL_Surface* gBackgroundSurface;
extern SDL_Surface* gFontSurface;
extern SDL_Surface* gClockBgSurface;

extern Uint32 bgColor;

extern bool IS_RUNNING;

extern Uint32 start;
extern Uint32 delay;
extern Uint32 counter;

extern Uint32 glyphColor;

extern int gClockOneTimer;

bool init(void);
void EventLoop(void);
void Render(void);
void Update(void);
void WaitLoop(void);
void CloseApp(void);
void UpdateTimeInSeconds(void);

void LoadBMPS(void);

void PlayAlarm(void);

#endif
