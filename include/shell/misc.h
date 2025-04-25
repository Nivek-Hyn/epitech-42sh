/*
** EPITECH PROJECT, 2025
** misc
** File description:
** minishell2
*/

#ifndef MISC_H
    #define MISC_H

void sh_vclose(int n, ...);
int sh_vclose_ret(int code, int n, ...);
char **sh_tabreader(const char *filename, int *length);
bool_t sh_regin(const char *string, const char **string_list);

#endif
