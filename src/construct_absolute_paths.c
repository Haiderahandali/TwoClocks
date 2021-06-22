#include "construct_absolute_paths.h"

int StringLength(char* path)
{
    int length = 0;
    while (*path++)
        ++length;
    return length;
}

void appendTwoStrings(char* dest, char* source)
{
    int srcStrLength = StringLength(dest);
    while (*source)
    {
        dest[srcStrLength++] = *source++;
    }

    dest[srcStrLength] = *source;
}
/*       1 2 3 4     */
//gets the length of path right after `/` so if your exe is at /bin/bash, this function should return 4; / b i n
int GetExeDirLength(char* path, int length)
{
    for (int i = 0; i < 3; ++i)
    {
        while (path[--length] != '/')
            if (!length)
                return 0;
    }

    return length;
}
void CopyStrings(char* dest, char* source)

{

    while (*source)
    {
        *dest++ = *source++;
    }
    *(dest) = *source;
}
void ConstuctPaths(char* audioPath,
    char* clockBackgroundPath,
    char* appBackGroundPath,
    char* fontPath)
{

    char* font      = "/assets/Green_FontMap.bmp";
    char* clockbg   = "/assets/Clock_BG.bmp";
    char* appBg     = "/assets/relax_bg.bmp";
    char* audiopath = "/assets/clockAlarm.mp3";

    int bufsize = 512;
    char fullExecutablePath[bufsize];
    _NSGetExecutablePath(fullExecutablePath, &bufsize);
    int pathCharCount      = StringLength(fullExecutablePath);
    int executableDirIndex = GetExeDirLength(fullExecutablePath, pathCharCount);

    fullExecutablePath[executableDirIndex] = '\0';

    char temp[100];

    CopyStrings(temp, fullExecutablePath);
    appendTwoStrings(temp, font);
    CopyStrings(fontPath, temp);

    CopyStrings(temp, fullExecutablePath);
    appendTwoStrings(temp, clockbg);
    CopyStrings(clockBackgroundPath, temp);

    CopyStrings(temp, fullExecutablePath);
    appendTwoStrings(temp, appBg);
    CopyStrings(appBackGroundPath, temp);

    CopyStrings(temp, fullExecutablePath);
    appendTwoStrings(temp, audiopath);
    CopyStrings(audioPath, temp);
}
