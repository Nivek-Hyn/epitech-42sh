/*
** EPITECH PROJECT, 2025
** sh_get_pwd
** File description:
** 42sh
*/

#include <unistd.h>
#include "my.h"
#include "colors.h"
#include <sys/types.h>
#include <pwd.h>

char *sh_get_pwd(void)
{
    char *cwd = getcwd(NULL, 0);

    if (cwd == NULL)
        return my_strdup("<unknown path>");
    return cwd;
}

char *sh_get_pwd_color(void)
{
    char *cwd = getcwd(NULL, 0);

    if (cwd == NULL)
        return my_strdup(COL_RED "<unknown path>" COL_RESET);
    return cwd;
}
