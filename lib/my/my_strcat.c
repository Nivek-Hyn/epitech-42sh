/*
** EPITECH PROJECT, 2024
** my_strcat
** File description:
** Day 7, Task 2
*/

#include <stdio.h>
#include <stdlib.h>
#include "my.h"

char *my_strcat(char *dest, const char *src)
{
    int i = 0;

    if (dest == NULL || src == NULL)
        return NULL;
    for (i = 0; src[i] != '\0'; i++)
        dest[i] = src[i];
    return dest;
}
