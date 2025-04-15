/*
** EPITECH PROJECT, 2024
** my_chrdup
** File description:
** Day 8, Task 1
*/

#include <stdlib.h>
#include "my.h"
#include "utils.h"

char *my_chrdup(const char src)
{
    char *dest = NULL;

    if (src == '\0')
        return NULL;
    dest = malloc(sizeof(char) * 2);
    if (dest == NULL)
        return NULL;
    dest[0] = src;
    dest[1] = '\0';
    return dest;
}
