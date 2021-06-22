#pragma once
int StringLength(char* path);
void appendTwoStrings(char* dest, char* source);
int GetExeDirLength(char* path, int length);
void CopyStrings(char* dest, char* source);

void ConstuctPaths(char* audioPath,
    char* clockBackgroundPath,
    char* appBackGroundPath,
    char* fontPath);
