#include "shell.h"

void trim_spaces(char *str)
{
    int start = 0, end = strlen(str) - 1, i;
    
    while (isspace(str[start]))
        start++;
    
    while (end > start && isspace(str[end]))
        end--;
    
    for (i = start; i <= end; i++)
        str[i - start] = str[i];
    
    str[end - start + 1] = '\0';
}
