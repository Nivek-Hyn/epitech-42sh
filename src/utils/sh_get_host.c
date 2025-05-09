/*
** EPITECH PROJECT, 2025
** sh_get_pwd
** File description:
** 42sh
*/

#include <unistd.h>
#include "my.h"
#include "colors.h"
#include "shell/misc.h"
#include <sys/types.h>
#include <pwd.h>

char *sh_get_host(void)
{
    char hostname[MAX_HOSTNAME_LEN + 1];

    my_memset(hostname, '\0', MAX_HOSTNAME_LEN + 1);
    if (gethostname(hostname, MAX_HOSTNAME_LEN) == FUNC_FAILED)
        return my_strdup("<unknown path>");
    return my_strdup(hostname);
}

char *sh_get_host_color(void)
{
    char hostname[MAX_HOSTNAME_LEN + 1];

    my_memset(hostname, '\0', MAX_HOSTNAME_LEN + 1);
    if (gethostname(hostname, MAX_HOSTNAME_LEN) == FUNC_FAILED)
        return my_strdup(COL_RED "<unknown path>" COL_RESET);
    return my_strdup(hostname);
}
