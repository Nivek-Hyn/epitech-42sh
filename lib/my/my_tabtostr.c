/*
** EPITECH PROJECT, 2024
** my_tabdup
** File description:
** day 4, task 3
** my_strlen.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "my.h"
#include "utils.h"

static int get_length_of_strs(const char **src)
{
    int len = 0;

    if (src == NULL)
        return FUNC_FAILED;
    for (int i = 0; src[i] != NULL; i++)
        len += my_strlen(src[i]);
    return len;
}

static int write_string(const char **src, char *new_str)
{
    char *curr_write = NULL;

    if (src == NULL || new_str == NULL)
        return FUNC_FAILED;
    curr_write = new_str;
    for (int i = 0; src[i] != NULL; i++) {
        curr_write = my_strcpy_sp(curr_write, src[i]);
        if (curr_write == NULL)
            return FUNC_FAILED;
        if (src[i + 1] != NULL) {
            *curr_write = ' ';
            curr_write++;
        }
    }
    return FUNC_SUCCESS;
}

char *my_tabtostr(const char **src)
{
    int tab_len = my_tablen((const void **) src) - 1;
    int chr_len = get_length_of_strs(src);
    char *new_str = NULL;

    if (src == NULL || tab_len < 0 || chr_len <= 0)
        return NULL;
    new_str = malloc(sizeof(char) * (chr_len + tab_len + 1));
    if (new_str == NULL)
        return NULL;
    if (write_string(src, new_str) == FUNC_FAILED) {
        free(new_str);
        return NULL;
    }
    if (tab_len == 0)
        new_str[chr_len + tab_len] = '\0';
    return new_str;
}
