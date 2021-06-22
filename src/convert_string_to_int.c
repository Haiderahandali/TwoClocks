#include "convert_string_to_int.h"
int IsNumber(char c)
{
    if ((c >= '0') && (c <= '9'))
    {
        return 1;
    }

    else

    {
        return 0;
    }
}

int ConvertStringToInt(char const* str)
{
    char currentCharacter;
    int result = 0;
    while ((currentCharacter = *str++))
    {
        if (IsNumber(currentCharacter))
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
