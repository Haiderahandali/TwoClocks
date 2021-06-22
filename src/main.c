#include "SDL.h"
#include "core.h"
#include "load_bmp.h"
#include "convert_string_to_int.h"

int main(int argc, char* argv[])
{
    if (argc == 3)
    {
        FIRST_CLOCK_TIME = ConvertStringToInt(argv[1]);
        SECND_CLOCK_TIME = ConvertStringToInt(argv[2]);
    }
    else
    {
        FIRST_CLOCK_TIME = 14;
        SECND_CLOCK_TIME = 20;
    }

    if (!init())
    {
        SDL_Log("couldn't init the app terminating..\n");
    }

    while (IS_RUNNING)
    {
        EventLoop();
        Render();
        Update();
        WaitLoop();
    }

    CloseApp();
}
