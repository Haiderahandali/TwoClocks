#include "SDL.h"
#include "core.h"
#include "load_bmp.h"
#include "convert_string_to_int.h"

int main(int argc, char* argv[])
{
    if (argc == 3)
    {
        gFirstClockTime  = ConvertStringToInt(argv[1]);
        gSecondClockTime = ConvertStringToInt(argv[2]);
    }
    else
    {
        gFirstClockTime  = 14;
        gSecondClockTime = 20;
    }

    if (!init())
    {
        SDL_Log("couldn't init the app terminating..\n");
        return -1;
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
