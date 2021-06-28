#ifndef CORE_H
#define CORE_H
#include "SDL.h"
#include "sdl_surfaces_header.h"

#define SDL_SUCCESS 0
#define FAILED_TO_INIT_WINDOW NULL
#define FAILED_TO_GET_WINDOW_SURFACE NULL

extern int gFirstClockTime;
extern int gSecondClockTime;
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define true 1
#define false 0
typedef _Bool bool;
// typedef enum
// {
//     false,
//     true
// } bool;

extern bool IS_RUNNING;

bool init(void);
void EventLoop(void);
void Render(void);
void Update(void);
void WaitLoop(void);
void CloseApp(void);
void UpdateTimeInSeconds(void);

void LoadBMPS(void);

#endif
