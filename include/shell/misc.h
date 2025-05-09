/*
** EPITECH PROJECT, 2025
** misc
** File description:
** minishell2
*/

#include "my.h"

#ifndef MISC_H
    #define MISC_H

    #define MAX_HOSTNAME_LEN 500

void sh_vclose(int n, ...);
int sh_vclose_ret(int code, int n, ...);
char **sh_tabreader(const char *filename, int *length);
bool_t sh_regin(const char *string, const char **string_list);

int is_digit(char c);
int is_number(char *str);
int my_atoi(char *str);

char *sh_get_user(void);
char *sh_get_user_color(void);
char *sh_get_pwd(void);
char *sh_get_pwd_color(void);
char *sh_get_host(void);
char *sh_get_host_color(void);

#endif
