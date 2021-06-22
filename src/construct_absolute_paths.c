#include "construct_absolute_paths.h"

#define PATH_BUFFER_SIZE 100
#define ABSOLUTE_PATH_BUFFER_SIZE 512

int StringLength(char const* path) // use strlen
{
    int length = 0;
    while (*path++)
    {
        ++length;
    }
    return length;
}

void AppendTwoStrings(char* dest, char const* source) // user strcat
{
    int srcStrLength = StringLength(dest);
    while (*source)
    {
        dest[srcStrLength++] = *source++;
    }

    dest[srcStrLength] = *source;
}

int GetExeDirLength(char const* path, int length)
{
    //the path is usually /someDir/projectDir/bin/Debug/App
    //so we need to get the projectDir by removing 3 '/'
    for (int i = 0; i < 3; ++i)
    {
        while (path[--length] != '/')
        {
            if (!length)
            {
                return 0;
            }
        }
    }

    return length;
}

void CopyStrings(char* dest, char const* source) // use strcpy
{
    while (*source)
    {
        *dest++ = *source++;
    }
    *(dest) = *source;
}

void ConstuctPaths(
    char* audioPath,
    char* clockBackgroundPath,
    char* appBackGroundPath,
    char* fontPath)
{
    char const* const font      = "/assets/Green_FontMap.bmp";
    char const* const clockbg   = "/assets/Clock_BG.bmp";
    char const* const appBg     = "/assets/relax_bg.bmp";
    char const* const audiopath = "/assets/clockAlarm.mp3";

    int bufsize = ABSOLUTE_PATH_BUFFER_SIZE;
    char fullExecutablePath[bufsize];
    _NSGetExecutablePath(fullExecutablePath, &bufsize);
    int pathCharCount      = StringLength(fullExecutablePath);
    int executableDirIndex = GetExeDirLength(fullExecutablePath, pathCharCount);

    fullExecutablePath[executableDirIndex] = '\0';

    char temp[PATH_BUFFER_SIZE];

    CopyStrings(temp, fullExecutablePath);
    AppendTwoStrings(temp, font);
    CopyStrings(fontPath, temp);

    CopyStrings(temp, fullExecutablePath);
    AppendTwoStrings(temp, clockbg);
    CopyStrings(clockBackgroundPath, temp);

    CopyStrings(temp, fullExecutablePath);
    AppendTwoStrings(temp, appBg);
    CopyStrings(appBackGroundPath, temp);

    CopyStrings(temp, fullExecutablePath);
    AppendTwoStrings(temp, audiopath);
    CopyStrings(audioPath, temp);
}
