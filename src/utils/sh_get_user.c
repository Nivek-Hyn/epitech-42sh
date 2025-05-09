/*
** EPITECH PROJECT, 2025
** sh_get_user
** File description:
** 42sh
*/

#include <unistd.h>
#include "my.h"
#include "colors.h"
#include <sys/types.h>
#include <pwd.h>

char *sh_get_user(void)
{
    uid_t uid = geteuid();
    struct passwd *pw = getpwuid(uid);

    if (pw == NULL)
        return my_strdup("<unidentified>");
    return my_strdup(pw->pw_name);
}

char *sh_get_user_color(void)
{
    uid_t uid = geteuid();
    struct passwd *pw = getpwuid(uid);

    if (pw == NULL)
        return my_strdup(COL_RED "<unidentified>" COL_RESET);
    return my_strdup(pw->pw_name);
}
