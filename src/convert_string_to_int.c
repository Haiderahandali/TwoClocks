#include "convert_string_to_int.h"

static int IsDigit(char c)
{
    return ((c >= '0') && (c <= '9'));
}

int ConvertStringToInt(char const* str)
{
    char currentCharacter;
    int result = 0;
    while ((currentCharacter = *str++))
    {
        if (IsDigit(currentCharacter))
        {
            result *= 10;
            result += (currentCharacter - '0');
        }
        else
        {
            __builtin_printf("Error not a number ... defaulting to 60 seconds \n");
            return 60;
        }
    }
    return result;
}
