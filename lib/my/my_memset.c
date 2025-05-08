/*
** EPITECH PROJECT, 2025
** my_memset
** File description:
** libmy
*/

#include <stdlib.h>

void *my_memset(void *s, int c, size_t n)
{
    unsigned char *ptr = (unsigned char *)s;

    if (!s)
        return NULL;
    for (size_t i = 0; i < n; i++)
        ptr[i] = (unsigned char)c;
    return s;
}
