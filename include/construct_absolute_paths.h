#ifndef CONSTRUCT_PATH_H
#define CONSTRUCT_PATH_H

int StringLength(char const* path);
void AppendTwoStrings(char* dest, char const* source);
int GetExeDirLength(char const* path, int length);
void CopyStrings(char* dest, char const* source);

void ConstuctPaths(
    char* audioPath,
    char* clockBackgroundPath,
    char* appBackGroundPath,
    char* fontPath);
#endif
