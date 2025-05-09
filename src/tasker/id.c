/*
** EPITECH PROJECT, 2025
** id
** File description:
** minishell2
*/

#include <stdio.h>
#include "shell/parser.h"
#include "shell/config/built_in.h"
#include "my.h"

sh_tasker_type_t sh_tasker_identify_type(sh_prsent_t *args)
{
    if (args == NULL)
        return SH_TASKER_UNKNOWN;
    for (; args != NULL; args = args->next)
        if (my_strcmp(args->entry, "") != CMP_EXACT)
            break;
    if (args == NULL)
        return SH_TASKER_UNKNOWN;
    for (int i = 0; sh_builtins[i].command != NULL; i++)
        if (my_strcmp(sh_builtins[i].command, args->entry) == CMP_EXACT)
            return SH_TASKER_BUILTIN;
    return SH_TASKER_COMMAND;
}
