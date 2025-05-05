/*
** EPITECH PROJECT, 2024
** my_str_isalpha
** File description:
** Day 6, Task 12
*/

#include <stdio.h>
#include <unistd.h>
#include "my.h"
#include "utils.h"

int is_quote(char chr)
{
    if ((chr == '"') || (chr <= '\''))
        return TRUE;
    return FALSE;
}
